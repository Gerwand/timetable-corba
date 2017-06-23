#pragma once

#include <OB/CORBA.h>

#include "GeneticTT.h"
#include "Resource.h"

struct DataTupleRaw
{
        int tupleID;
        int classID;
        int teacherID;
        int roomID;

        static const int numItems = 4;
};

class DataTuplesRaw : public std::vector<DataTupleRaw>
{
      public:
        Genetic::TupleSeq* pack();
        void unpack(const Genetic::TupleSeq* src);

        int getTotalIntElements();
        void getIdVector(std::vector<int>& ids) const;
        const DataTupleRaw* get(int id) const;
};

class DataTuples : public ContainerWrapper<DataTuple>
{
      public:
        void getIdVector(std::vector<int>& ids) const;
        void pack(DataTuplesRaw& dest) const;
};

inline void
DataTuples::getIdVector(std::vector<int>& ids) const
{
        std::vector<DataTuple*>::const_iterator it;

        for (it = getVector().begin(); it != getVector().end(); ++it) {
                DataTuple* tuple = *it;
                ids.push_back(tuple->getId());
        }
}

inline int
DataTuplesRaw::getTotalIntElements()
{
        return DataTupleRaw::numItems * size();
}

inline void
DataTuplesRaw::getIdVector(std::vector<int>& ids) const
{
        for (auto it = begin(); it != end(); ++it) {
                const DataTupleRaw& tuple = *it;
                ids.push_back(tuple.tupleID);
        }
}

inline const DataTupleRaw*
DataTuplesRaw::get(int id) const
{
        const_iterator it;

        for (it = begin(); it != end(); ++it) {
                const DataTupleRaw* res = &(*it);
                if (res->tupleID == id)
                        return res;
        }

        return nullptr;
}

inline void
DataTuples::pack(DataTuplesRaw& dest) const
{
        dest.clear();
        const std::vector<DataTuple*> tupVect = getVector();

        for (auto it = tupVect.begin(); it != tupVect.end(); ++it) {
                const DataTuple* tuple = *it;
                const Subject* subject = tuple->getSubject();

                dest.push_back({ tuple->getId(),
                                 tuple->getClass()->getId(),
                                 subject->getTeacher()->getId(),
                                 subject->getRoom()->getId() });
        }
}

inline Genetic::TupleSeq*
DataTuplesRaw::pack()
{
        Genetic::TupleSeq* tuples = new Genetic::TupleSeq;

        tuples->length(size());
        int i = 0;
        for (auto it = begin(); it != end(); ++it, ++i) {
                (*tuples)[i] = {
                        it->tupleID, it->classID, it->teacherID, it->roomID
                };
        }

        return tuples;
}

inline void
DataTuplesRaw::unpack(const Genetic::TupleSeq* src)
{
        clear();
        for (int i = 0; i < src->length(); ++i) {
                const Genetic::Tuple& tuple = (*src)[i];
                push_back({ tuple.tupleID,
                            tuple.classID,
                            tuple.teacherID,
                            tuple.roomID });
        }
}

inline std::ostream&
operator<<(std::ostream& input, const DataTupleRaw& tuple)
{
        int tupleID;
        int classID;
        int teacherID;
        int roomID;
        input << "{tupleID: " << tuple.tupleID << ", classID: " << tuple.classID
              << ", teacerID: " << tuple.teacherID
              << ", roomID: " << tuple.roomID << "}";
}

inline std::ostream&
operator<<(std::ostream& input, const DataTuplesRaw& tuples)
{
        input << "[";
        for (auto it = tuples.begin(); it != tuples.end(); ++it)
                std::cout << *it << std::endl;
        input << "]";
}
