#define BOOST_TEST_MODULE cpp_template Unit Tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <stdexcept>
#include "lru_cache.h"

const LruCache::TKey key_0 = 2;
const LruCache::TKey key_1 = 3;
const LruCache::TKey key_2 = 5;

const LruCache::TValue val_0 = 42;
const LruCache::TValue val_1 = 84;
const LruCache::TValue val_2 = 99;

BOOST_AUTO_TEST_CASE(Ctor_CapacityIsZero_ThrowsInvalidArgument)
{
    // Arrange/Act
    auto action = [&]()
    {
        LruCache cache(0);
    };

    // Assert
    BOOST_CHECK_THROW(action(), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(GetFirstAdded_TwoIntsSetCapacityIsOne_ReturnsInvalid)
{
    // Arrange
    LruCache cache(1);
    cache.set(key_0, val_0);
    cache.set(key_1, val_1);
    LruCache::TValue expected = LruCache::INVALID;

    // Act
    LruCache::TValue actual = cache.get(key_0);

    // Assert
    BOOST_CHECK_EQUAL(actual, expected);
}

// BOOST_AUTO_TEST_CASE(GetSecondAdded_TwoIntsSetCapacityIsOne_ReturnsSecondValue)
// {
//     // Arrange
//
//     // Act
//
//     // Assert
//     BOOST_TEST(false);
// }
//
// BOOST_AUTO_TEST_CASE(GetFirstAdded_FourIntsSetCapacityIsThree_ReturnsInvalid)
// {
//     // Arrange
//
//     // Act
//
//     // Assert
//     BOOST_TEST(false);
// }
//
// BOOST_AUTO_TEST_CASE(GetSecondAdded_FourIntsSetCapacityIsThree_ReturnsSecondValue)
// {
//     // Arrange
//
//     // Act
//
//     // Assert
//     BOOST_TEST(false);
// }
//
// BOOST_AUTO_TEST_CASE(GetFourthAdded_FourIntsSetCapacityIsThree_ReturnsFourthValue)
// {
//     // Arrange
//
//     // Act
//
//     // Assert
//     BOOST_TEST(false);
// }
