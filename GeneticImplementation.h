#ifndef _GENETIC_IMPLEMENTATION_H_
#define _GENETIC_IMPLEMENTATION_H_

#include <OB/CORBA.h>

#include "GeneticTT_skel.h"

#include "RandWrapper.h"
#include "RandomInterface.h"

#include "DataTuples.h"
#include "Population.h"

class GeneticImplementation : virtual public POA_Genetic::GeneticTimeTable,
                              virtual public PortableServer::RefCountServantBase
{
      public:
        GeneticImplementation(CORBA::ORB_var orb,
                              Genetic::RandomProvider* randGen)
        {
                _randGen = randGen;
                _orb = orb;
        }
        ~GeneticImplementation() {}

        // Update of the parameters used in genetic algorithm
        virtual void updateParameters(
          ::CORBA::Long maxFitness,
          ::CORBA::Long periods,
          ::CORBA::Long naturalSelection) throw(::CORBA::SystemException)
          override
        {
                _maxFitness = maxFitness;
                _periods = periods;
                _naturalSelection = naturalSelection;
        }

        // Get initial, random number of population without any rules
        virtual ::Genetic::IndividualSeq* getRandomPopulation(
          ::CORBA::Long number,
          ::CORBA::Float_out meanFitness) throw(::CORBA::SystemException)
          override;

        // Crossover population given as parameter
        virtual ::Genetic::IndividualSeq* mate(
          ::CORBA::Long number,
          ::CORBA::Float_out meanFitness,
          ::CORBA::Long_out perfectPos) throw(::CORBA::SystemException)
          override;

        // Tuples setters and getters
        // Getter
        virtual ::Genetic::TupleSeq* tuples() throw(
          ::CORBA::SystemException) override
        {
                return _tuples.pack();
        }
        virtual void tuples(const ::Genetic::TupleSeq& tuples) throw(
          ::CORBA::SystemException) override
        {
                _tuples.unpack(&tuples);
                _tuples.getIdVector(_tuplesInd);
        }

        //
        // IDL:Genetic/GeneticTimeTable/population:1.0
        //
        virtual ::Genetic::IndividualSeq* population() throw(
          ::CORBA::SystemException) override
        {
                return _oldPopulation.pack();
        }
        virtual void
        population(const ::Genetic::IndividualSeq& population) throw(
          ::CORBA::SystemException) override
        {
                _oldPopulation.unpack(&population);
        }

      private:
        Genetic::RandomProvider* _randGen;
        CORBA::ORB_var _orb;

        Population _oldPopulation;
        DataTuplesRaw _tuples;

        long _maxFitness;
        long _periods;
        long _naturalSelection;

        std::vector<int> _tuplesInd;
};

#endif
