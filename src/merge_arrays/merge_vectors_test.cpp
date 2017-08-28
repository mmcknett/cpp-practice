#define BOOST_TEST_MODULE merge_vectors Unit Tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "merge_vectors.h"
#include <vector>

static const std::vector<float> empty;
static const std::vector<float> anySortedVector {1.0f, 2.0f, 3.0f};

void assertVectorsEqual(const std::vector<float>& expected, const std::vector<float>& actual)
{
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(expected), std::end(expected), std::begin(actual), std::end(actual));
}

void merge_LhsAndRhs_ReturnsExpected(
    const std::vector<float>& lhs,
    const std::vector<float>& rhs,
    const std::vector<float>& expected)
{
    // Act
    auto result = merge(lhs, rhs);

    // Assert
    assertVectorsEqual(expected, result);
}

BOOST_AUTO_TEST_CASE(Merge_TwoEmptyFloatVectors_ReturnsEmptyVector)
{
    merge_LhsAndRhs_ReturnsExpected(empty, empty, empty);
}

BOOST_AUTO_TEST_CASE(Merge_OneEmptyOneSortedVector_ReturnsCopyOfSortedVector)
{
    merge_LhsAndRhs_ReturnsExpected(empty, anySortedVector, anySortedVector);
}

BOOST_AUTO_TEST_CASE(Merge_OneSortedOneEmptyVector_ReturnsCopyOfSortedVector)
{
    merge_LhsAndRhs_ReturnsExpected(anySortedVector, empty, anySortedVector);
}

BOOST_AUTO_TEST_CASE(Merge_TwoFloatVectorsLengthThree_MergesVectors)
{
    // Arrange
    const std::vector<float> lhs = {2.0f, 3.5f, 6.0f};
    const std::vector<float> rhs = {3.0f, 4.0f, 4.5f};
    const std::vector<float> expected = {2.0f, 3.0f, 3.5f, 4.0f, 4.5f, 6.0f};

    // Act/Assert
    merge_LhsAndRhs_ReturnsExpected(lhs, rhs, expected);
}

BOOST_AUTO_TEST_CASE(Merge_TwoFloatVectorsFirstSortsFirst_MergesVectors)
{
    // Arrange
    const std::vector<float> lhs = {2.0f, 3.5f, 6.0f, 7.0f};
    const std::vector<float> rhs = {8.0f, 10.0f, 10.5f};
    const std::vector<float> expected = {2.0f, 3.5f, 6.0f, 7.0f, 8.0f, 10.0f, 10.5f};

    // Act/Assert
    merge_LhsAndRhs_ReturnsExpected(lhs, rhs, expected);
}

BOOST_AUTO_TEST_CASE(Merge_TwoFloatVectorsSecondSortsFirst_MergesVectors)
{
    // Arrange
    const std::vector<float> lhs = {10.0f, 11.0f, 12.0f};
    const std::vector<float> rhs = {5.0f, 8.5f};
    const std::vector<float> expected = {5.0f, 8.5f, 10.0f, 11.0f, 12.0f};

    // Act/Assert
    merge_LhsAndRhs_ReturnsExpected(lhs, rhs, expected);
}

// BOOST_AUTO_TEST_CASE(MergeAll_NoVectors_ReturnsEmptyVector)
// {
// }
//
// BOOST_AUTO_TEST_CASE(MergeAll_OneVector_ReturnsSameVector)
// {
// }
//
// BOOST_AUTO_TEST_CASE(MergeAll_RaggedVectors_ReturnsMergedVector)
// {
// }
