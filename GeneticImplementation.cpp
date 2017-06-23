#include "GeneticImplementation.h"

// To .cpp file
// Get initial, random number of population without any rules
::Genetic::IndividualSeq*
GeneticImplementation::getRandomPopulation(
  ::CORBA::Long number,
  ::CORBA::Float_out meanFitness) throw(::CORBA::SystemException)
{
        size_t tuplesPerPeriod = _tuplesInd.size() / _periods;
        size_t rest = _tuplesInd.size() - _periods * tuplesPerPeriod;
        int i = 0;
        Population population;
        int totalFitness = 0;

        std::random_device rd;
        std::mt19937 gen(rd());

        for (size_t i = 0; i < number; ++i) {
                std::vector<int> curTuples = _tuplesInd;
                auto it = curTuples.begin();
                // Shuffle tuples ids
                std::shuffle(curTuples.begin(), curTuples.end(), gen);

                // Create new timetable
                Timetable* newIndividual = new Timetable(_periods);
                population.addIndividual(newIndividual);

                // Get period
                Period* period = nullptr;
                int n = -1;
                for (size_t k = 0; k < _periods * tuplesPerPeriod; ++k) {
                        if (k % tuplesPerPeriod == 0) {
                                ++n;
                                period = &((*newIndividual)[n]);
                                if (period == nullptr)
                                        period = &((*newIndividual)[n - 1]);
                        }

                        period->addTuple(*it);
                        ++it;
                }

                for (size_t k = 0; k < rest; ++k) {
                        period = &((*newIndividual)[k]);

                        period->addTuple(*it);
                        ++it;
                }
                totalFitness +=
                  _maxFitness - newIndividual->getClashes(_tuples);
        }

        meanFitness = (float)totalFitness / number;

        ::Genetic::IndividualSeq* inds = population.pack();

        return inds;
}

::Genetic::IndividualSeq*
GeneticImplementation::mate(
  ::CORBA::Long number,
  ::CORBA::Float_out meanFitness,
  ::CORBA::Long_out perfectPos) throw(::CORBA::SystemException)
{
        int totalFitness = 0;
        int pos = 0;
        perfectPos = -1;
        // Get worst case number of random number
        int randSize =
          (11 + _tuplesInd.size() * 2 + _periods) * number + number * 2;
        ::Genetic::RandomSeq* rands = _randGen->getRandomLong(randSize);
        RandWrapper randw = (rands);

        Population newPopulation;
        for (int i = 0; i < number; ++i) {
                Timetable* child = new Timetable(_periods);

                const Timetables& timetables = _oldPopulation.getPopulation();
                int p1Ind, p2Ind;
                do {
                        p1Ind = randw() % timetables.size();
                        p2Ind = randw() % timetables.size();
                } while (p1Ind == p2Ind);
                Timetable* parent1 = timetables[p1Ind];
                Timetable* parent2 = timetables[p2Ind];

                const Periods& periods1 = parent1->getPeriods();
                const Periods& periods2 = parent2->getPeriods();
                Periods& periodsc = child->getPeriods();

                // Copy genes
                Periods::const_iterator itp1, itp2;
                Periods::iterator itc;
                for (itp1 = periods1.begin(),
                    itp2 = periods2.begin(),
                    itc = periodsc.begin();
                     itp1 != periods1.end();
                     ++itp1, ++itp2, ++itc) {
                        int maxSize = std::min(itp1->getTuplesCount(),
                                               itp2->getTuplesCount());

                        if (maxSize == 0)
                                break;

                        // RAND
                        int random = randw();
                        size_t crossoverSite = random % maxSize;

                        const std::vector<int>& idp1 = itp1->getTuplesIDs();
                        const std::vector<int>& idp2 = itp2->getTuplesIDs();
                        std::vector<int>& idc = itc->getTuplesIDs();

                        for (size_t i = 0; i < crossoverSite && i < idp1.size();
                             ++i)
                                idc.push_back(idp1[i]);
                        for (size_t i = crossoverSite; i < idp2.size(); ++i)
                                idc.push_back(idp2[i]);
                }

                // Mutate
                child->mutate(randw);
                // Remove duplicates
                child->removeDuplicates(_tuplesInd, randw);
                // Restore state
                child->fillMissing(_tuplesInd, randw);

                int clashes;

                clashes = child->getClashes(_tuples);

                int fitness = _maxFitness - clashes;

                if (fitness == _maxFitness)
                        perfectPos = pos;

                if (fitness - _naturalSelection >= 0) {
                        totalFitness += fitness;
                        newPopulation.addIndividual(child);
                        ++pos;
                } else {
                        delete child;
                }
        }

        int newSize = newPopulation.getPopulation().size();
        meanFitness = newSize > 0 ? (double)totalFitness / newSize : 0;

        // Convert to descriptors
        ::Genetic::IndividualSeq* indiv = newPopulation.pack();

        return indiv;
}
