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

template <typename T>
struct ItRange
{
    typename std::vector<T>::const_iterator itCurrent;
    typename std::vector<T>::const_iterator itEnd;
};

template <typename T>
struct ItRangeComparer
{
    bool operator()(const ItRange<T>& lhs, const ItRange<T>& rhs)
    {
        return *(lhs.itCurrent) < *(rhs.itCurrent);
    }
};

template <typename T>
std::vector<ItRange<T>> getNonEmptyRanges(const std::vector<std::vector<T>>& vectors)
{
    std::vector<ItRange<T>> its;
    its.reserve(vectors.size());

    // Get the start & end iterators for all the vectors.
    std::transform(std::begin(vectors), std::end(vectors), std::back_inserter(its),
        [](const std::vector<T>& vector) -> ItRange<T> { return { std::begin(vector), std::end(vector) }; });

    // Remove any iterators for empty vectors.
    auto itNewEnd = std::remove_if(std::begin(its), std::end(its),
        [](const ItRange<T>& range) { return range.itCurrent == range.itEnd; });
    its.erase(itNewEnd, std::end(its));

    return its;
}

// Find the iterator range whose current value is the minimum of all current values,
// grab the current value, then increment the current iterator for that range.
// Remove the range if it's empty.
template <typename T>
T getNextMinElementAndHandleEmpty(std::vector<ItRange<T>>& its)
{
    auto itMinRange = std::min_element(std::begin(its), std::end(its), ItRangeComparer<T>());

    // Extract result and increment.
    auto& itMinOfAllVectors = itMinRange->itCurrent;
    T minValue = *itMinOfAllVectors;
    ++itMinOfAllVectors;

    // Remove the iterators if we've reached the end of their vector.
    if (itMinRange->itCurrent == itMinRange->itEnd)
    {
        its.erase(itMinRange);
    }

    return minValue;
}

// A version of mergeAll with less time and memory complexity.
template <typename T>
std::vector<T> mergeAllFast(const std::vector<std::vector<T>>& vectors)
{
    std::vector<T> result;

    // Optimization: Consider using list instead of vector as we're going to Remove
    // iterators when we're done with them.
    std::vector<ItRange<T>> its = getNonEmptyRanges(vectors);

    while(!its.empty())
    {
        result.push_back(getNextMinElementAndHandleEmpty(its));
    }

    return result;
}

#endif /* end of include guard: MERGE_VECTORS_H_INCLUDED */
