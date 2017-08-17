#include "appointment_ranges.h"

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

int appendRangesFromAppointments(
    vector<Appointment>::const_iterator itStartAppts,
    vector<Appointment>::const_iterator itEndAppts,
    int startTime,
    int endTime,
    Pattern fillPattern,
    Ranges& ranges)
{
    int priorRangeEndMinute = startTime;

    for(auto itCurr = itStartAppts; itCurr != itEndAppts; ++itCurr)
    {
        const Appointment& appt = *itCurr;

        if (appt.state == FreeBusy::Free ||
            !appt.endsAfter(priorRangeEndMinute))
        {
            // Ignore free appointments and appointments that don't
            // end after the range we've already considered.
            continue;
        }

        bool spacingRequired = appt.startsAfter(priorRangeEndMinute);

        // Add an empty range if there is space between the last end and this start.
        if (spacingRequired)
        {
            ranges.addRange(
                Range {
                    positionOfMinute(priorRangeEndMinute),
                    positionOfMinute(appt.startMinute),
                    fillPattern
                });
        }

        // Use the prior end or the current start, whichever is later.
        int adjustedStart = std::max(priorRangeEndMinute, appt.startMinute);
        if (appt.state == FreeBusy::Tentative)
        {
            auto itNextNonOverlappingAppt =
                find_if(itCurr, itEndAppts,
                    [&appt](const Appointment& other) { return other.startMinute >= appt.endMinute; });

            priorRangeEndMinute = appendRangesFromAppointments(
                next(itCurr, 1),
                itNextNonOverlappingAppt,
                adjustedStart,
                appt.endMinute,
                Pattern::Hashed /*fillPattern*/,
                ranges);
        }
        else
        {
            if (appt.endMinute - adjustedStart > 0)
            {
                Pattern newPattern = getPatternFromState(appt.state);
                ranges.addRange(
                    Range {
                        positionOfMinute(adjustedStart),
                        positionOfMinute(appt.endMinute),
                        newPattern
                    });

                priorRangeEndMinute = appt.endMinute;
            }
        }
    }

    // Fill any leftover ranges.
    if (priorRangeEndMinute < endTime)
    {
        ranges.addRange(
            Range {
                positionOfMinute(priorRangeEndMinute),
                positionOfMinute(endTime),
                fillPattern
            });
        priorRangeEndMinute = endTime;
    }

    return priorRangeEndMinute;
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

     appendRangesFromAppointments(
        begin(appointments),
        end(appointments), //itFirstTentative,
        0 /*startTime*/,
        c_lastMinute /*endTime*/,
        Pattern::Empty /*fillPattern*/,
        ranges);

    cerr << "Ranges:" << endl;
    for(auto rg : ranges.getRanges())
    {
        cerr << "\tRg: " << rg.yStart << " to " << rg.yEnd << ": "
            << (rg.pattern == Pattern::Empty ? "empty" : (rg.pattern == Pattern::Solid ? "Solid" : "Hashed"))
            << endl;
    }

    return ranges.getRanges();
}
