#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED

// Given two sorted arrays, merge them into a new sorted array.
template <typename T>
T* merge(const T lhs[], size_t lhsSize, const T rhs[], size_t rhsSize)
{
    if (lhsSize + rhsSize == 0)
    {
        return nullptr;
    }

    const T* currRhs = rhs;
    const T* currLhs = lhs;
    const T* lhsEnd = lhs + lhsSize;
    const T* rhsEnd = rhs + rhsSize;

    T* result = new T[lhsSize + rhsSize];
    T* currResult = result;

    while(currRhs != rhsEnd && currLhs != lhsEnd)
    {
        *(currResult++) = *currLhs < *currRhs ? *currLhs++ : *currRhs++;
    }

    while (currRhs != rhsEnd)
    {
        *(currResult++) = *currRhs++;
    }

    while (currLhs != lhsEnd)
    {
        *(currResult++) = *currLhs++;
    }

    return result;
}

#endif /* end of include guard: MERGE_H_INCLUDED */
