#define BOOST_TEST_MODULE merge_vectors Unit Tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "merge_vectors.h"
#include <vector>

static const std::vector<float> empty;
static const std::vector<float> vector1 {1.0f, 2.0f, 3.0f};

void assertVectorsEqual(const std::vector<float>& expected, const std::vector<float>& actual)
{
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(expected), std::end(expected), std::begin(actual), std::end(actual));
}

BOOST_AUTO_TEST_CASE(Merge_TwoEmptyFloatVectors_ReturnsEmptyVector)
{
    // Arrange
    const auto& lhs = empty;
    const auto& rhs = empty;
    const auto& expected = empty;

    // Act
    auto result = merge(lhs, rhs);

    // Assert
    assertVectorsEqual(expected, result);
}

BOOST_AUTO_TEST_CASE(Merge_OneEmptyOneSortedVector_ReturnsCopyOfSortedVector)
{
    // Arrange
    const auto& lhs = empty;
    const auto& rhs = vector1;
    const auto& expected = vector1;

    // Act
    auto result = merge(lhs, rhs);

    // Assert
    assertVectorsEqual(expected, result);
}

BOOST_AUTO_TEST_CASE(Merge_OneSortedOneEmptyVector_ReturnsCopyOfSortedVector)
{
    // Arrange
    const auto& lhs = vector1;
    const auto& rhs = empty;
    const auto& expected = vector1;

    // Act
    auto result = merge(lhs, rhs);

    // Assert
    assertVectorsEqual(expected, result);
}

// BOOST_AUTO_TEST_CASE(Merge_TwoFloatVectorsLengthThree_MergesVectors)
// {
// }
//
// BOOST_AUTO_TEST_CASE(Merge_TwoFloatVectorsFirstSortsFirst_MergesVectors)
// {
// }
//
// BOOST_AUTO_TEST_CASE(Merge_TwoFloatVectorsSecondSortsFirst_MergesVectors)
// {
// }
//
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
