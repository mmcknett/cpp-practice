#define BOOST_TEST_MODULE appointment_ranges Unit Tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "appointment_ranges.h"

using namespace std;

const double c_pixelsPerMinute = 1.0;

double positionOfMinute(int minute)
{
    return c_pixelsPerMinute * minute;
}

BOOST_AUTO_TEST_CASE(getRangesFromAppointments_NoAppointments_ReturnsOneEmptyRange)
{
    // Arrange
    vector<Appointment> noAppointments;
    vector<Range> expectedRanges {
        Range {
            positionOfMinute(0),
            positionOfMinute(c_lastMinute),
            Pattern::Empty,
        }
    };

    // Act
    vector<Range> actualRanges = getRangesFromAppointments(noAppointments);

    // Assert
    BOOST_CHECK_EQUAL(expectedRanges.size(), actualRanges.size());
    BOOST_TEST(equal(begin(actualRanges), end(actualRanges), begin(expectedRanges)));
}

BOOST_AUTO_TEST_CASE(getRangesFromAppointments_OneFreeAppointment_ReturnsOneEmptyRange)
{
    // Arrange
    vector<Appointment> oneFreeappointment {
        Appointment {
            60,
            120,
            FreeBusy::Free,
        }
    };
    vector<Range> expectedRanges {
        Range {
            positionOfMinute(0),
            positionOfMinute(c_lastMinute),
            Pattern::Empty,
        }
    };

    // Act
    vector<Range> actualRanges = getRangesFromAppointments(oneFreeappointment);

    // Assert
    BOOST_CHECK_EQUAL(expectedRanges.size(), actualRanges.size());
    BOOST_TEST(equal(begin(actualRanges), end(actualRanges), begin(expectedRanges)));
}
