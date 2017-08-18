#include "appointment.h"

bool Appointment::startsAfter(int minute) const
{
    return startMinute > minute;
}

bool Appointment::endsAfter(int minute) const
{
    return endMinute > minute;
}

bool operator<(const Appointment& lhs, const Appointment& rhs)
{
    if (lhs.startMinute != rhs.startMinute)
    {
        return lhs.startMinute < rhs.startMinute;
    }
    else if(lhs.endMinute != lhs.startMinute)
    {
        // Looks like a bug! Bug we actually want the larger ranges
        // to sort before the shorter ranges, all other things being equal.
        return lhs.endMinute > rhs.endMinute;
    }
    else /* (lhs.state != rhs.state)*/
    {
        return lhs.state < rhs.state;
    }
}
