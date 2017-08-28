#ifndef MERGE_VECTORS_H_INCLUDED
#define MERGE_VECTORS_H_INCLUDED

#include <vector>

// Given two sorted vectors, merge them into a new sorted vector.
template <typename T>
std::vector<T> merge(const std::vector<T>& lhs, const std::vector<T>& rhs)
{
    return std::vector<T>();
}

// Given a vector of sorted vectors, merge them into a new sorted vector.
template <typename T>
std::vector<T> mergeAll(const std::vector<std::vector<T>>& vectors)
{
}

#endif /* end of include guard: MERGE_VECTORS_H_INCLUDED */
