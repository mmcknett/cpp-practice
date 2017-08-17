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

BOOST_AUTO_TEST_CASE(getRangesFromAppointments_OneTentativeAppointment_ReturnsEmptyHashedEmpty)
{
    // Arrange
    const int c_apptStart = 60;
    const int c_apptEnd = 120;
    vector<Appointment> oneTentativeAppointment {
        Appointment { c_apptStart, c_apptEnd, FreeBusy::Tentative }
    };
    vector<Range> expectedRanges {
        Range { positionOfMinute(0), positionOfMinute(c_apptStart), Pattern::Empty },
        Range { positionOfMinute(c_apptStart), positionOfMinute(c_apptEnd), Pattern::Hashed },
        Range { positionOfMinute(c_apptEnd), positionOfMinute(c_lastMinute), Pattern::Empty }
    };

    // Act
    vector<Range> actualRanges = getRangesFromAppointments(oneTentativeAppointment);

    // Assert
    BOOST_CHECK_EQUAL(expectedRanges.size(), actualRanges.size());
    BOOST_TEST(equal(begin(actualRanges), end(actualRanges), begin(expectedRanges)));
}

BOOST_AUTO_TEST_CASE(getRangesFromAppointments_OneBusyAppointment_ReturnsEmptySolidEmpty)
{
    // Arrange
    const int c_apptStart = 60;
    const int c_apptEnd = 120;
    vector<Appointment> oneTentativeAppointment {
        Appointment { c_apptStart, c_apptEnd, FreeBusy::Busy }
    };
    vector<Range> expectedRanges {
        Range { positionOfMinute(0), positionOfMinute(c_apptStart), Pattern::Empty },
        Range { positionOfMinute(c_apptStart), positionOfMinute(c_apptEnd), Pattern::Solid },
        Range { positionOfMinute(c_apptEnd), positionOfMinute(c_lastMinute), Pattern::Empty }
    };

    // Act
    vector<Range> actualRanges = getRangesFromAppointments(oneTentativeAppointment);

    // Assert
    BOOST_CHECK_EQUAL(expectedRanges.size(), actualRanges.size());
    BOOST_TEST(equal(begin(actualRanges), end(actualRanges), begin(expectedRanges)));
}

BOOST_AUTO_TEST_CASE(getRangesFromAppointments_TwoSeparateTentativeAppointments_ReturnsEmptyHashedEmptyHashedEmpty)
{
    // Arrange
    const int c_apptStart1 = 60;
    const int c_apptEnd1 = 120;
    const int c_apptStart2 = 180;
    const int c_apptEnd2 = 240;
    vector<Appointment> twoSeparateTentativeAppointments {
        Appointment { c_apptStart1, c_apptEnd1, FreeBusy::Tentative },
        Appointment { c_apptStart2, c_apptEnd2, FreeBusy::Tentative }
    };
    vector<Range> expectedRanges {
        Range { positionOfMinute(0), positionOfMinute(c_apptStart1), Pattern::Empty },
        Range { positionOfMinute(c_apptStart1), positionOfMinute(c_apptEnd1), Pattern::Hashed },
        Range { positionOfMinute(c_apptEnd1), positionOfMinute(c_apptStart2), Pattern::Empty },
        Range { positionOfMinute(c_apptStart2), positionOfMinute(c_apptEnd2), Pattern::Hashed },
        Range { positionOfMinute(c_apptEnd2), positionOfMinute(c_lastMinute), Pattern::Empty },
    };

    // Act
    vector<Range> actualRanges = getRangesFromAppointments(twoSeparateTentativeAppointments);

    // Assert
    BOOST_CHECK_EQUAL(expectedRanges.size(), actualRanges.size());
    BOOST_TEST(equal(begin(actualRanges), end(actualRanges), begin(expectedRanges)));
}

BOOST_AUTO_TEST_CASE(getRangesFromAppointments_TwoAdjacentTentativeAppointments_ReturnsEmptyHashedEmpty)
{
    // Arrange
    const int c_apptStart1 = 60;
    const int c_apptEnd1 = 120;
    const int c_apptStart2 = 120;
    const int c_apptEnd2 = 240;
    vector<Appointment> twoSeparateTentativeAppointments {
        Appointment { c_apptStart1, c_apptEnd1, FreeBusy::Tentative },
        Appointment { c_apptStart2, c_apptEnd2, FreeBusy::Tentative }
    };
    vector<Range> expectedRanges {
        Range { positionOfMinute(0), positionOfMinute(c_apptStart1), Pattern::Empty },
        Range { positionOfMinute(c_apptStart1), positionOfMinute(c_apptEnd2), Pattern::Hashed },
        Range { positionOfMinute(c_apptEnd2), positionOfMinute(c_lastMinute), Pattern::Empty },
    };

    // Act
    vector<Range> actualRanges = getRangesFromAppointments(twoSeparateTentativeAppointments);

    // Assert
    BOOST_CHECK_EQUAL(expectedRanges.size(), actualRanges.size());
    BOOST_TEST(equal(begin(actualRanges), end(actualRanges), begin(expectedRanges)));
}
