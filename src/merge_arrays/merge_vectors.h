#ifndef MERGE_VECTORS_H_INCLUDED
#define MERGE_VECTORS_H_INCLUDED

#include <vector>
#include <iostream>

template <typename T>
void printVector(const std::vector<T>& result)
{
    std::cerr << "Result: [";
    for (auto it = std::begin(result); it != std::end(result); ++it)
    {
        std::cerr << *it << " ";
    }
    std::cerr << "]" << std::endl;
}

// Given two sorted vectors, merge them into a new sorted vector.
template <typename T>
std::vector<T> merge(const std::vector<T>& lhs, const std::vector<T>& rhs)
{
    std::vector<T> result;
    result.reserve(lhs.size() + rhs.size());

    auto itRhs = std::begin(rhs);
    auto itLhs = std::begin(lhs);

    while(itRhs != std::end(rhs) && itLhs != std::end(lhs))
    {
        result.push_back(*itLhs < *itRhs ? *itLhs++ : *itRhs++);
    }

    if (itLhs == std::end(lhs))
    {
        std::copy(itRhs, std::end(rhs), std::back_inserter(result));
    }
    else if (itRhs == std::end(rhs))
    {
        std::copy(itLhs, std::end(lhs), std::back_inserter(result));
    }

    // For debugging
    // printVector(result);

    return result;
}

// Given a vector of sorted vectors, merge them into a new sorted vector.
template <typename T>
std::vector<T> mergeAll(const std::vector<std::vector<T>>& vectors)
{
    std::vector<T> result;

    if (vectors.size() > 0)
    {
        result = vectors[0];
        for (auto itVecs = std::next(std::begin(vectors), 1); itVecs < std::end(vectors); ++itVecs)
        {
            result = merge<T>(result, *itVecs);
        }
    }

    return result;
}

// A version of mergeAll with less time and memory complexity.
template <typename T>
std::vector<T> mergeAllFast(const std::vector<std::vector<T>>& vectors)
{
    std::vector<T> result;

    if (vectors.size() > 0)
    {
        result = vectors[0];
    }

    return result;
}

#endif /* end of include guard: MERGE_VECTORS_H_INCLUDED */
