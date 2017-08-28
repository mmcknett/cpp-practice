#define BOOST_TEST_MODULE merge_vectors Unit Tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "merge_vectors.h"
#include <vector>

BOOST_AUTO_TEST_CASE(Merge_TwoEmptyFloatVectors_ReturnsEmptyVector)
{
    // Arrange
    std::vector<float> lhs, rhs;

    // Act
    auto result = merge(lhs, rhs);

    // Assert
    BOOST_CHECK_EQUAL(0u, result.size());
}

// BOOST_AUTO_TEST_CASE(Merge_OneEmptyOneSortedVector_ReturnsCopyOfSortedVector)
// {
// }
//
// BOOST_AUTO_TEST_CASE(Merge_OneSortedOneEmptyVector_ReturnsCopyOfSortedVector)
// {
// }
//
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
