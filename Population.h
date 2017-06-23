#pragma once

#include <OB/CORBA.h>

#include "Timetable.h"

#include "GeneticTT.h"

#include <vector>

typedef std::vector<Timetable*> Timetables;

#define MIN_POP_SIZE 10

class Population
{
      public:
        Population(const Population& population);
        Population(const Timetables& timetables);
        Population(){};
        ~Population();

        const Population& operator=(const Population& population);
        const Population& operator=(const Timetables& timetables);

        const Timetables& getPopulation() { return _timetables; }

        void addIndividual(Timetable* individual);
        bool hasExtincted() { return _timetables.size() < MIN_POP_SIZE; }
        void clear();

        Genetic::IndividualSeq* pack();
        void unpack(const Genetic::IndividualSeq* dest);
        void append(const Genetic::IndividualSeq* dest);

      private:
        Timetables _timetables;
};

inline Population::Population(const Population& population)
{
        *this = population;
}

inline Population::Population(const Timetables& timetables)
{
        *this = timetables;
}

inline Population::~Population()
{
        clear();
}

inline const Population&
Population::operator=(const Population& population)
{
        clear();
        const Timetables& timetables = population._timetables;

        Timetables::const_iterator it;
        for (it = timetables.begin(); it != timetables.end(); ++it) {
                _timetables.push_back(new Timetable(**it));
        }

        return *this;
}

inline const Population&
Population::operator=(const Timetables& timetables)
{
        clear();
        _timetables = timetables;

        return *this;
}

inline void
Population::clear()
{
        Timetables::iterator it;
        for (it = _timetables.begin(); it != _timetables.end(); ++it)
                delete *it;

        _timetables.clear();
}

inline void
Population::addIndividual(Timetable* individual)
{
        _timetables.push_back(individual);
}

inline std::ostream&
operator<<(std::ostream& out, Population& population)
{
        const Timetables& tts = population.getPopulation();
        out << "[";
        for (auto it = tts.begin(); it != tts.end(); ++it) {
                Timetable* tt = *it;
                out << *tt;
        }
        out << "]";
}
