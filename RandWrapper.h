#pragma once

#include "RandomImplementation.h"

#include <cstdlib>
#include <ctime>

class RandWrapper
{
      public:
        RandWrapper(Genetic::RandomSeq* rseq)
          : _rands(rseq)
        {
        }

        int operator()() { return !depleted() ? (*_rands)[_nextID++] : rand(); }

        bool depleted() { return _nextID >= _rands->length(); }

      private:
        Genetic::RandomSeq* _rands;
        int _nextID = 0;
};
