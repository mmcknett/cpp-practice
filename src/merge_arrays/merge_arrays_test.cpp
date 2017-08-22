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
