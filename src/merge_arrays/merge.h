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

    T* result = new T[lhsSize + rhsSize];
    T* currResult = result;
    const T* lhsEnd = lhs + lhsSize;
    const T* rhsEnd = rhs + rhsSize;

    for (const T* currRhs = rhs; currRhs != rhsEnd; ++currRhs)
    {
        *(currResult++) = *currRhs;
    }

    for (const T* currLhs = lhs; currLhs != lhsEnd; ++currLhs)
    {
        *(currResult++) = *currLhs;
    }

    return result;
}

#endif /* end of include guard: MERGE_H_INCLUDED */
