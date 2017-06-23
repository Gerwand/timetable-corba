#pragma once

#include "Period.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "RandWrapper.h"

typedef std::vector<Period> Periods;

class Timetable
{
      public:
        Timetable(int periodsNumber) { _periods.resize(periodsNumber); }
        Timetable(const Timetable& timetable) { _periods = timetable._periods; }

        Periods& getPeriods() { return _periods; }
        const Periods& getPeriods() const { return _periods; }
        int getPeriodsCount() const { return _periods.size(); }

        int getClashes(const DataTuplesRaw& tuples);
        int getFitness() const { return _fitness; }

        void mutate(RandWrapper& randw);
        void removeDuplicates(const std::vector<int>& ids, RandWrapper& randw);
        void fillMissing(const std::vector<int>& ids, RandWrapper& randw);

        void setFitness(int fitness) { _fitness = fitness; }
        Period& operator[](int n) { return _periods[n]; }
        const Period& operator[](int n) const { return _periods[n]; }

        void printPretty(std::ostream& stream, const DataTuples& tuples);

      private:
        Periods _periods;
        int _fitness = 0;
};

std::ostream&
operator<<(std::ostream& stream, const Timetable& timetable);
