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

BOOST_AUTO_TEST_CASE(Add_EmptyListToZero_ReturnsOneDigit)
{
    // Arrange
    intList emptyList;
    intList zero = {0};

    // Act
    intList result = Add(emptyList, zero);

    // Assert
    BOOST_TEST(result == zero);
}

BOOST_AUTO_TEST_CASE(Add_zeroToEmptyList_ReturnsOneDigit)
{
    // Arrange
    intList emptyList;
    intList zero = {0};

    // Act
    intList result = Add(zero, emptyList);

    // Assert
    BOOST_TEST(result == zero);
}

BOOST_AUTO_TEST_CASE(Add_zeroToZero_ReturnsOneDigitZero)
{
    // Arrange
    intList zero = {0};

    // Act
    intList result = Add(zero, zero);

    // Assert
    BOOST_TEST(result == zero);
}


BOOST_AUTO_TEST_CASE(Add_oneToThree_ReturnsOneDigitFour)
{
    // Arrange
    intList one = {1};
    intList three = {3};
    intList expected = {4};

    // Act
    intList result = Add(one, three);

    // Assert
    BOOST_TEST(result == expected);
}

BOOST_AUTO_TEST_CASE(Add_fourToSix_ReturnsTwoDigitTen)
{
    // Arrange
    intList four = {4};
    intList six = {6};
    intList expected = {0, 1};

    // Act
    intList result = Add(four, six);

    // Assert
    BOOST_TEST(result == expected);
}
