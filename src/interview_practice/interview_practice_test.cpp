#define BOOST_TEST_MODULE interview_practice Unit Tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "adder.h"

BOOST_AUTO_TEST_CASE(Add_EmptyLists_ReturnsEmptyList)
{
    // Arrange
    intList emptyList;

    // Act
    intList result = Add(emptyList, emptyList);

    // Assert
    BOOST_TEST(result == emptyList);
}
