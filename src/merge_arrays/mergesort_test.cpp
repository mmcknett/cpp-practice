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

BOOST_AUTO_TEST_CASE(MergeSort_OneElement_ReturnsOneElement)
{
    // Arrange
    std::vector<float> oneElement {1.0f};
    std::vector<float> expected {1.0f};

    // Act
    mergeSort(oneElement);

    // Assert
    assertVectorsEqual(expected, oneElement);
}

BOOST_AUTO_TEST_CASE(MergeSort_TwoSortedElements_ReturnsTwoSortedElements)
{
    // Arrange
    std::vector<float> elements {1.0f, 2.0f};
    std::vector<float> expected {1.0f, 2.0f};

    // Act
    mergeSort(elements);

    // Assert
    assertVectorsEqual(expected, elements);
}

BOOST_AUTO_TEST_CASE(MergeSort_TwoUnsortedElements_ReturnsTwoSortedElements)
{
    // Arrange
    std::vector<float> elements {2.0f, 1.0f};
    std::vector<float> expected {1.0f, 2.0f};

    // Act
    mergeSort(elements);

    // Assert
    assertVectorsEqual(expected, elements);
}

BOOST_AUTO_TEST_CASE(MergeSort_ThreeUnsortedElements_ReturnsThreeSortedElements)
{
    // Arrange
    std::vector<float> elements {3.0f, 2.0f, 1.0f};
    std::vector<float> expected {1.0f, 2.0f, 3.0f};

    // Act
    mergeSort(elements);

    // Assert
    assertVectorsEqual(expected, elements);
}

BOOST_AUTO_TEST_CASE(MergeSort_FourUnsortedElements_ReturnsFourSortedElements)
{
    // Arrange
    std::vector<float> elements {3.0f, 2.0f, 4.0f, 1.0f};
    std::vector<float> expected {1.0f, 2.0f, 3.0f, 4.0f};

    // Act
    mergeSort(elements);

    // Assert
    assertVectorsEqual(expected, elements);
}

BOOST_AUTO_TEST_CASE(MergeSort_TenUnsortedElements_ReturnsTenSortedElements)
{
    // Arrange
    std::vector<float> elements {3.0f, 9.0f, 2.0f, 6.0f, 4.0f, 0.0f, 1.0f, 7.0f, 8.0f, 5.0f};
    std::vector<float> expected {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};

    // Act
    mergeSort(elements);

    // Assert
    assertVectorsEqual(expected, elements);
}
