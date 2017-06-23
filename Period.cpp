#include "Period.h"

using namespace std;

int
Period::getClashes(const DataTuplesRaw& tuples)
{
        int clashes = 0;
        vector<int>::iterator it1, it2;
        for (it1 = _tuplesIDs.begin(); it1 != _tuplesIDs.end(); ++it1) {
                const DataTupleRaw* first = tuples.get(*it1);

                for (it2 = it1 + 1; it2 != _tuplesIDs.end(); ++it2) {
                        const DataTupleRaw* second = tuples.get(*it2);

                        if (first->classID == second->classID)
                                clashes++;

                        if (first->roomID == second->roomID)
                                clashes++;

                        if (first->teacherID == second->teacherID)
                                clashes++;
                }
        }

        return clashes;
}
