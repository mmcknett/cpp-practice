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

// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: 7 -> 0 -> 8

BOOST_AUTO_TEST_CASE(Add_342to465_Returns807)
{
    // Arrange
    intList lhs = {2, 4, 3};
    intList rhs = {5, 6, 4};
    intList expected = {7, 0, 8};

    // Act
    intList result = Add(lhs, rhs);

    // Assert
    BOOST_TEST(result == expected);
}

BOOST_AUTO_TEST_CASE(Add_999to1_Returns1000)
{
    // Arrange
    intList lhs = {9, 9, 9};
    intList rhs = {1};
    intList expected = {0, 0, 0, 1};

    // Act
    intList result = Add(lhs, rhs);

    // Assert
    BOOST_TEST(result == expected);
}

BOOST_AUTO_TEST_CASE(Add_1to999_Returns1000)
{
    // Arrange
    intList lhs = {1};
    intList rhs = {9, 9, 9};
    intList expected = {0, 0, 0, 1};

    // Act
    intList result = Add(lhs, rhs);

    // Assert
    BOOST_TEST(result == expected);
}

BOOST_AUTO_TEST_CASE(Add_1toAThousand9s_ReturnsTenToThe1001)
{
    // Arrange
    intList lhs = {1};
    intList rhs;
    for (int i = 0; i < 1000; ++i)
    {
        rhs.push_back(9);
    }

    intList expected;
    for (int i = 0; i < 1000; ++i)
    {
        expected.push_back(0);
    }
    expected.push_back(1);

    // Act
    intList result = Add(lhs, rhs);

    // Assert
    BOOST_TEST(result == expected);
}
