#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

#include "merge_vectors.h"

template <typename T>
void mergeSort(std::vector<T>& vector)
{
    if (vector.size() < 2)
    {
        return;
    }

    auto mid = std::next(std::begin(vector), vector.size() / 2);
    std::vector<T> lhs(std::begin(vector), mid);
    std::vector<T> rhs(mid, std::end(vector));

    mergeSort(lhs);
    mergeSort(rhs);
    vector = merge(lhs, rhs);
}

#endif /* end of include guard: MERGESORT_H_INCLUDED */
