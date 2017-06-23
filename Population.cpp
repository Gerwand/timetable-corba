#include "Population.h"

Genetic::IndividualSeq*
Population::pack()
{
        Genetic::IndividualSeq* packedPopulation = new Genetic::IndividualSeq;

        packedPopulation->length(_timetables.size());

        int i = 0;
        for (auto it = _timetables.begin(); it != _timetables.end(); ++it) {
                const Timetable* tt = *it;
                const Periods& periods = tt->getPeriods();

                Genetic::PeriodSeq& indiv = (*packedPopulation)[i++];
                indiv.length(periods.size());

                int p = 0;
                for (auto itp = periods.begin(); itp != periods.end(); ++itp) {
                        Genetic::LongSeq& genes = indiv[p++];
                        // Get genes as vector
                        const std::vector<int>& ids = itp->getTuplesIDs();

                        genes.length(ids.size());
                        // Copy genes and descriptors
                        int g = 0;
                        for (auto itg = ids.begin(); itg != ids.end(); ++itg)
                                genes[g++] = *itg;
                }
        }

        return packedPopulation;
}

void
Population::unpack(const Genetic::IndividualSeq* dest)
{
        clear();

        append(dest);
}

void
Population::append(const Genetic::IndividualSeq* dest)
{
        for (int i = 0; i < dest->length(); ++i) {
                const Genetic::PeriodSeq& indiv = (*dest)[i];
                Timetable* tt = new Timetable(indiv.length());
                _timetables.push_back(tt);
                Periods& periods = tt->getPeriods();

                int n = 0;
                for (auto itp = periods.begin(); itp != periods.end(); ++itp) {
                        Period& period = *itp;
                        Genetic::LongSeq genes = indiv[n++];

                        for (int k = 0; k < genes.length(); ++k)
                                period.getTuplesIDs().push_back(genes[k]);
                }
        }
}
