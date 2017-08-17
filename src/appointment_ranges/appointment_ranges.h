#ifndef APPOINTMENT_RANGES_INCLUDED
#define APPOINTMENT_RANGES_INCLUDED

#include <vector>

const int c_lastMinute = 24 * 60;

// Order matters for sorting.
enum class FreeBusy
{
    Busy = 0,
    Tentative = 1,
    Free = 2,
};

struct Appointment
{
    int startMinute;
    int endMinute;
    FreeBusy state;
};

enum class Pattern
{
    Empty = 0,
    Hashed = 1,
    Solid = 2,
};

struct Range
{
    double yStart;
    double yEnd;
    Pattern pattern;
};

inline bool operator==(const Range& lhs, const Range& rhs)
{
    return lhs.yStart == rhs.yStart &&
        lhs.yEnd == rhs.yEnd &&
        lhs.pattern == rhs.pattern;
}

double positionOfMinute(int minute);
std::vector<Range> getRangesFromAppointments(std::vector<Appointment>& appointments);

#endif /* end of include guard: APPOINTMENT_RANGES_INCLUDED */
