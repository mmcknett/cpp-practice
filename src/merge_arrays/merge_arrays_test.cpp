#define BOOST_TEST_MODULE merge_arrays Unit Tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "merge.h"

BOOST_AUTO_TEST_CASE(Merge_TwoEmptyFloatArrays_ReturnsNull)
{
    // Arrange
    float array1[] = {};
    float array2[] = {};
    size_t size1 = 0;
    size_t size2 = 0;

    // Act
    float* result = merge(array1, size1, array2, size2);

    // Assert
    BOOST_CHECK(!result);
    delete[] result;
}

BOOST_AUTO_TEST_CASE(Merge_OneEmptyOneSortedArray_ReturnsCopyOfSortedArray)
{
    // Arrange
    float array1[] = {};
    size_t size1 = 0;
    float array2[] = {1.0f, 2.0f, 3.0f};
    size_t size2 = 3;

    // Act
    float* result = merge(array1, size1, array2, size2);

    // Assert
    BOOST_CHECK(std::equal(std::begin(array2), std::end(array2), result));
    delete[] result;
}

BOOST_AUTO_TEST_CASE(Merge_OneSortedOneEmptyArray_ReturnsCopyOfSortedArray)
{
    // Arrange
    float array1[] = {1.0f, 2.0f, 3.0f};
    size_t size1 = 3;
    float array2[] = {};
    size_t size2 = 0;

    // Act
    float* result = merge(array1, size1, array2, size2);

    // Assert
    BOOST_CHECK(std::equal(std::begin(array1), std::end(array1), result));
    delete[] result;
}

BOOST_AUTO_TEST_CASE(Merge_TwoFloatArraysLengthThree_MergesArrays)
{
    // Arrange
    const float array1[] = {2.0f, 3.5f, 6.0f};
    const size_t size1 = 3;
    const float array2[] = {3.0f, 4.0f, 4.5f};
    const size_t size2 = 3;

    const float expected[] = {2.0f, 3.0f, 3.5f, 4.0f, 4.5f, 6.0f};

    // Act
    float* result = merge(array1, size1, array2, size2);

    // Assert
    BOOST_CHECK(std::equal(std::begin(expected), std::end(expected), result));
    delete[] result;
}

BOOST_AUTO_TEST_CASE(Merge_TwoFloatArraysFirstSortsFirst_MergesArrays)
{
    // Arrange
    const float array1[] = {2.0f, 3.5f, 6.0f, 7.0f};
    const size_t size1 = 4;
    const float array2[] = {8.0f, 10.0f, 10.5f};
    const size_t size2 = 3;

    const float expected[] = {2.0f, 3.5f, 6.0f, 7.0f, 8.0f, 10.0f, 10.5f};

    // Act
    float* result = merge(array1, size1, array2, size2);

    // Assert
    BOOST_CHECK(std::equal(std::begin(expected), std::end(expected), result));
    delete[] result;
}

BOOST_AUTO_TEST_CASE(Merge_TwoFloatArraysSecondSortsFirst_MergesArrays)
{
    // Arrange
    const float array1[] = {10.0f, 11.0f, 12.0f};
    const size_t size1 = 3;
    const float array2[] = {5.0f, 8.5f};
    const size_t size2 = 2;

    const float expected[] = {5.0f, 8.5f, 10.0f, 11.0f, 12.0f};

    // Act
    float* result = merge(array1, size1, array2, size2);

    // Assert
    BOOST_CHECK(std::equal(std::begin(expected), std::end(expected), result));
    delete[] result;
}

BOOST_AUTO_TEST_CASE(MergeAll_NoArrays_ReturnsEmptyArray)
{
    // Arrange
    const float *arrays[] {};
    const size_t sizes[] {};

    // Act
    float* result = mergeAll(arrays, 0, sizes);

    // Assert
    BOOST_CHECK(!result);
    delete[] result;
}

// Helper function for deleting arrays of arrays...
// We've begun the descent into madness.
template<typename T>
void deleteArrays(const T* arrays[], size_t numArrays)
{
    for (auto it = arrays; it != arrays + numArrays; ++it)
    {
        delete[] *it;
    }
}

BOOST_AUTO_TEST_CASE(MergeAll_OneArray_ReturnsSameArray)
{
    // Arrange
    const float* arrays[] = {
        new float[3] {1.0f, 2.0f, 3.0f}
    };
    const size_t sizes[] = {3};

    const float expected[] {1.0f, 2.0f, 3.0f};

    // Act
    float* result = mergeAll(arrays, 1, sizes);

    // Assert
    BOOST_CHECK(std::equal(std::begin(expected), std::end(expected), result));
    delete[] result;
    deleteArrays(arrays, 1);
}

// You could probably generalizre this with variadic templates...
// I'm not sure how you'd initialize the arrays variable, though.
struct RaggedArray
{
    static constexpr size_t numArrays = 3;
    const float* arrays[numArrays];
    static constexpr size_t numExpected = 3 + 2 + 4;
    const float expected[numExpected];
    const size_t sizes[numArrays];

    // Behold the esoteric C++ ragged array construction.  Essentially, you
    // MUST declare each entry in the array on the heap or else require that
    // each entry is fixed size.  (This might be undesirable -- say you have
    // five lists, one of which has 1000 entries and the others of which have
    // only 4 entries.  Declaring that would require allocating space for 1000
    // entries, even for the arrays that only need 4.  So because we don't want
    // float[4][3], we use float*[3].)
    // Excellent explanation on StackOverflow: https://stackoverflow.com/questions/4810664/how-do-i-use-arrays-in-c/4810668#4810668
    // This is why you use vector<vector<float>> instead.
    RaggedArray()
        : arrays {
            new float[3] {1.0f, 2.0f, 3.0f},
            new float[2] {1.5f, 5.0f},
            new float[4] {0.5f, 2.5f, 4.0f, 6.0f}
        },
        expected {0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 4.0f, 5.0f, 6.0f},
        sizes {3, 2, 4}
    {
    }

    ~RaggedArray()
    {
        deleteArrays(arrays, numArrays);
    }
};

BOOST_FIXTURE_TEST_CASE(MergeAll_RaggedArrays_ReturnsMergedArray, RaggedArray)
{
    // Arrange
    // Arrange is entirely in the test fixture.

    // Act
    float* result = mergeAll(arrays, numArrays, sizes);

    // Assert
    BOOST_CHECK(std::equal(expected, expected + numExpected, result));
    delete[] result;
}
