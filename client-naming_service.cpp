#include <OB/CORBA.h>
#include <OB/CosNaming.h>

#include <iomanip>
#include <iostream>
#include <omp.h>
#include <vector>

#include "GeneticTT.h"

#include "DataParser.h"
#include "Population.h"

#define TOTAL_BIRTH 5000

void
run(std::vector<Genetic::GeneticTimeTable*> servers,
    const std::string& inputFile,
    const std::string& outputFile,
    int periods);

int
main(int argc, char* argv[])
{
        if (argc != 8) {
                std::cout
                  << "Usage: " << argv[0]
                  << " -ORBnaming  serv_num input_file output_file periods"
                  << std::endl;
                exit(-1);
        }

        try {
                // Initialize client ORB
                CORBA::ORB_var vOrb = CORBA::ORB_init(argc, argv);

                // Locate Name Service
                CORBA::Object_var vObject =
                  vOrb->resolve_initial_references("NameService");
                CosNaming::NamingContext_var vNamingContext =
                  CosNaming::NamingContext::_narrow(vObject);

                // Prepare object with "server name" query
                std::string pname(argv[1]);
                int len = atoi(argv[2]);
                std::vector<Genetic::GeneticTimeTable*> servers;
                for (int i = 0; i < len; ++i) {
                        std::string srvName = pname + std::to_string(i);
                        CosNaming::Name implName;
                        implName.length(1);
                        implName[0].id = CORBA::string_dup(srvName.c_str());
                        implName[0].kind = CORBA::string_dup("");
                        // Get remote object reference from Name Service
                        CORBA::Object_var vCorbaObj =
                          vNamingContext->resolve(implName);
                        servers.push_back(
                          Genetic::GeneticTimeTable::_narrow(vCorbaObj));
                }

                // OMP configuration
                omp_set_dynamic(0); // Disable dynamic teams, to make sure that
                                    // each server is called from other thread
                // Configure omp threads number
                omp_set_num_threads(servers.size());

                run(servers, argv[3], argv[4], atoi(argv[5]));
        } catch (CORBA::SystemException& e) {
                std::cout << "Exception: " << e.reason() << std::endl;
                return 1;
        }

        return 0;
}

void
run(std::vector<Genetic::GeneticTimeTable*> servers,
    const std::string& inputFile,
    const std::string& outputFile,
    int periods)
{
        float fitness, newFitness;
        DataTuples tuples;
        DataResources resources;
        DataParser parser(inputFile);
        int naturalSelection = 0;
        Genetic::IndividualSeq* indiv;
        Population oldGeneration, newGeneration;
        int birthPerNode = TOTAL_BIRTH / servers.size();

        ////////////////////////////////////////////////////////////////
        //                         Parse input resources
        ////////////////////////////////////////////////////////////////
        if (parser.getResources(resources, tuples)) {
                std::cout << "Error getting resources from file " << inputFile
                          << "!" << std::endl;
                exit(-1);
        }

        DataTuplesRaw tuplesRaw;
        tuples.pack(tuplesRaw);

        // Send tuples on server
        Genetic::TupleSeq* tupleSeq = tuplesRaw.pack();
        std::cout << "Converted ok, size: " << tupleSeq->length() << std::endl;

#pragma omp parallel for
        for (int i = 0; i < servers.size(); ++i) {
                Genetic::GeneticTimeTable* server = servers[i];
                server->updateParameters(100, periods, naturalSelection);
                server->tuples(*tupleSeq);
        }
        delete tupleSeq;

        // Initialize population
        Genetic::GeneticTimeTable* server = servers[0];
        indiv = server->getRandomPopulation(200, fitness);

        oldGeneration.append(indiv);
        naturalSelection = std::round(fitness);

        // Send population to all servers

        indiv = oldGeneration.pack();
        for (int i = 0; i < servers.size(); ++i) {
                Genetic::GeneticTimeTable* server = servers[i];
                server->updateParameters(100, periods, naturalSelection);
                server->population(*indiv);
        }

        Timetable perfect(periods);
        bool found = false;
        while (true) {

                newGeneration.clear();
                // Now we should do mating on each server in parallel
                ////////////////////////////////////////////////////////////////
                //                         Parallel mating
                ////////////////////////////////////////////////////////////////
                std::vector<float> fitnesses;
                std::vector<int> sizes;

#pragma omp parallel for private(indiv)
                for (int i = 0; i < servers.size(); ++i) {
                        Genetic::GeneticTimeTable* server = servers[i];
                        int perfectInd;
                        float fit;

                        indiv = server->mate(birthPerNode, fit, perfectInd);

#pragma omp critical
                        { // Will store all fitnesses and sizes

                                fitnesses.push_back(fit);
                                sizes.push_back(indiv->length());
                        }
                        int sizeBefore = newGeneration.getPopulation().size();
                        newGeneration.append(indiv);

                        ////////////////////////////////////////////////////////
                        //           Check for perfect child (-1, not exist)
                        ////////////////////////////////////////////////////////
                        if (perfectInd >= 0) {
                                int ind = sizeBefore + perfectInd;
#pragma omp critical
                                perfect = *newGeneration.getPopulation()[ind];
                                found = true;
                        }
                }

                ////////////////////////////////////////////////////////////////
                //                       Check for result
                ////////////////////////////////////////////////////////////////
                if (found)
                        break;

                ////////////////////////////////////////////////////////////////
                //                   New population validation
                ////////////////////////////////////////////////////////////////
                // check if new population is existing
                if (newGeneration.hasExtincted()) {
                        naturalSelection--;

#pragma omp parallel for
                        for (int i = 0; i < servers.size(); ++i) {
                                Genetic::GeneticTimeTable* server = servers[i];
                                server->updateParameters(
                                  100, periods, naturalSelection);
                        }
                        std::cout << "Population extincted, naturalSelection: "
                                  << naturalSelection << std::endl;
                        continue;
                }

                ////////////////////////////////////////////////////////////////
                //                        Fitness calculate
                ////////////////////////////////////////////////////////////////
                int totalFits = 0;
                for (int i = 0; i < sizes.size(); ++i)
                        totalFits += sizes[i];

                newFitness = 0;
                for (int i = 0; i < fitnesses.size(); ++i)
                        newFitness +=
                          fitnesses[i] * (sizes[i] / (float)totalFits);

                ////////////////////////////////////////////////////////////////
                //                        Generation update
                ////////////////////////////////////////////////////////////////
                // Decide whetever swap population
                if (newFitness >= fitness) {
                        fitness = newFitness;
                        std::cout
                          << "Population swapped, naturalSelection: "
                          << naturalSelection << ",fitness: " << fitness
                          << ", size: " << newGeneration.getPopulation().size()
                          << std::endl;
                        ++naturalSelection;
                        oldGeneration = newGeneration;

                        // Pack and broadcast
                        indiv = oldGeneration.pack();

#pragma omp parallel for
                        for (int i = 0; i < servers.size(); ++i) {
                                Genetic::GeneticTimeTable* server = servers[i];
                                server->updateParameters(
                                  100, periods, naturalSelection);
                                server->population(*indiv);
                        }
                } else {
                        std::cout
                          << "Population not swapped, naturalSelection: "
                          << naturalSelection << ", fitness: " << fitness
                          << ", new fitness: " << newFitness << std::endl;
                }
        }

        ////////////////////////////////////////////////////////////////////////
        //                                  Result
        ////////////////////////////////////////////////////////////////////////
        if (found) {
                perfect.printPretty(std::cout, tuples);

                // Save to file
                std::ofstream dest;
                dest.open(outputFile.c_str());
                perfect.printPretty(dest, tuples);
                dest.close();
        } else {
                std::cout << "Something went wrong..." << std::endl;
        }
}
