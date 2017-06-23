#ifndef _RANDOM_IMPLEMENTATION_H_
#define _RANDOM_IMPLEMENTATION_H_

#include <OB/CORBA.h>

#include <random>

#include "RandomInterface_skel.h"

class RandomImplementation : virtual public POA_Genetic::RandomProvider,
                             virtual public PortableServer::RefCountServantBase
{
      public:
        RandomImplementation(CORBA::ORB_var orb)
        {
                _orb = orb;
                std::random_device rd; // Will be used to obtain a seed for the
                                       // random number engine
                _gen.seed(rd());
        }

        virtual ::Genetic::RandomSeq* getRandomLong(::CORBA::Long num) throw(
          ::CORBA::SystemException) override
        {
                ::Genetic::RandomSeq* rands = new ::Genetic::RandomSeq;
                rands->length(num);
                for (int i = 0; i < num; ++i) {
                        (*rands)[i] = _dist(_gen);
                }

                return rands;
        }

      private:
        CORBA::ORB_var _orb;
        std::mt19937 _gen;
        std::uniform_int_distribution<int> _dist;
};

#endif
