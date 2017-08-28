#define BOOST_TEST_MODULE merge_vectors Unit Tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "mergesort.h"
#include <vector>

const std::vector<float> c_empty;

void assertVectorsEqual(const std::vector<float>& expected, const std::vector<float>& actual)
{
    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(expected), std::end(expected), std::begin(actual), std::end(actual));
}

BOOST_AUTO_TEST_CASE(MergeSort_Empty_ReturnsEmpty)
{
    // Arrange
    std::vector<float> empty;

    // Act
    mergeSort(empty);

    // Assert
    assertVectorsEqual(c_empty, empty);
}
