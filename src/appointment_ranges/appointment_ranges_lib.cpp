#include "appointment_ranges.h"
#include "conversions.h"
#include "rangemaker.h"

using namespace std;

bool operator==(const Range& lhs, const Range& rhs)
{
    return lhs.yStart == rhs.yStart &&
        lhs.yEnd == rhs.yEnd &&
        lhs.pattern == rhs.pattern;
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

Pattern getPatternFromState(FreeBusy state)
{
    switch(state)
    {
    case FreeBusy::Busy:
        return Pattern::Solid;
    case FreeBusy::Tentative:
        return Pattern::Hashed;
    default:
        return Pattern::Empty;
    }
}

bool Appointment::startsAfter(int minute) const
{
    return startMinute > minute;
}

bool Appointment::endsAfter(int minute) const
{
    return endMinute > minute;
}

void Ranges::addRange(Range&& newRange)
{
    // Check if the previous added pattern is the same.  If so, consolidate.
    if (!ranges.empty() &&
        ranges.back().yEnd >= newRange.yStart &&
        ranges.back().pattern == newRange.pattern)
    {
        ranges.back().yEnd = newRange.yEnd;
    }
    else
    {
        ranges.push_back(newRange);
    }
}

const vector<Range>& Ranges::getRanges() const
{
    return ranges;
}


#include <iostream> // for cerr tracing

vector<Range> getRangesFromAppointments(const vector<Appointment>& appointmentsIn)
{
    Ranges ranges;

    vector<Appointment> appointments(appointmentsIn);
    sort(begin(appointments), end(appointments));

    // Tracing
    cerr << "Appointments:" << endl;
    for(auto appt : appointments)
    {
        cerr << "\tAppt: " << appt.startMinute << " to " << appt.endMinute << ": "
            << (appt.state == FreeBusy::Free ? "Free" : (appt.state == FreeBusy::Busy ? "Busy" : "Tentative"))
            << endl;
    }

    RangeMaker rangeMaker(
        Pattern::Empty /*fillPattern*/,
        ranges);

    rangeMaker.appendAppointments(
        begin(appointments),
        end(appointments),
        0 /*startTime*/,
        c_lastMinute /*endTime*/);

    cerr << "Ranges:" << endl;
    for(auto rg : ranges.getRanges())
    {
        cerr << "\tRg: " << rg.yStart << " to " << rg.yEnd << ": "
            << (rg.pattern == Pattern::Empty ? "empty" : (rg.pattern == Pattern::Solid ? "Solid" : "Hashed"))
            << endl;
    }

    return ranges.getRanges();
}
