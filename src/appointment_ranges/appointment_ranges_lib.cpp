#include "appointment_ranges.h"

using namespace std;

bool operator<(const Appointment& lhs, const Appointment& rhs)
{
    if (lhs.state != rhs.state)
    {
        return lhs.state < rhs.state;
    }
    else if (lhs.startMinute != rhs.startMinute)
    {
        return lhs.startMinute < rhs.startMinute;
    }
    else // endMinute unequal
    {
        // Looks like a bug! Bug we actually want the larger ranges
        // to sort before the shorter ranges, all other things being equal.
        return lhs.endMinute > rhs.endMinute;
    }
}

void removeFreeAppointments(vector<Appointment>& appointments)
{
    auto itNewEndAppts = remove_if(
        begin(appointments),
        end(appointments),
        [](const Appointment & appt) { return appt.state == FreeBusy::Free; }
    );
    appointments.erase(itNewEndAppts, end(appointments));
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

int appendRangesFromAppointments(
    vector<Appointment>::const_iterator itStartAppts,
    vector<Appointment>::const_iterator itEndAppts,
    vector<Range>& ranges)
{
    int currentEnd = 0;

    for_each(itStartAppts, itEndAppts,
        [&ranges, &currentEnd](const Appointment& appt)
        {
            bool adjacentToPriorRange = false;

            // Ignore anything that ends prior to or at the end of the previous window,
            // since anything before now takes precedence.
            if (appt.endMinute > currentEnd)
            {
                // Add an empty range if there is space between the last end and this start.
                if (appt.startMinute > currentEnd)
                {
                    ranges.push_back( Range{ positionOfMinute(currentEnd), positionOfMinute(appt.startMinute), Pattern::Empty });
                }
                else
                {
                    // Ranges are adjacent; allow collapsing.
                    adjacentToPriorRange = true;
                }

                // Use the prior end or the current start, whichever is later.
                int adjustedStart = std::max(currentEnd, appt.startMinute);

                // Use this range if it's non-zero.
                if (appt.endMinute - adjustedStart > 0)
                {
                    // Check if the previous added pattern is the same.  If so, consolidate.
                    Pattern newPattern = getPatternFromState(appt.state);
                    if (adjacentToPriorRange && !ranges.empty() && ranges.back().pattern == newPattern)
                    {
                        ranges.back().yEnd = positionOfMinute(appt.endMinute);
                    }
                    else
                    {
                        ranges.push_back( Range{ positionOfMinute(adjustedStart), positionOfMinute(appt.endMinute), newPattern});
                    }
                }

                currentEnd = appt.endMinute;
            }
        }
    );

    return currentEnd;
}

// GDB isn't happy on my machine
#include <iostream>

vector<Range> getRangesFromAppointments(vector<Appointment>& appointments)
{
    vector<Range> ranges;

    sort(begin(appointments), end(appointments));

    // Tracing
    cerr << "Appointments:" << endl;
    for(auto appt : appointments)
    {
        cerr << "\tAppt: " << appt.startMinute << " to " << appt.endMinute << ": "
            << (appt.state == FreeBusy::Free ? "Free" : (appt.state == FreeBusy::Busy ? "Busy" : "Tentative"))
            << endl;
    }

    removeFreeAppointments(appointments);

    // Busy will be the first section, then there will be a tentative section.
    auto itFirstTentative = find_if(begin(appointments), end(appointments),
        [](const Appointment& appt) { return appt.state == FreeBusy::Tentative; });

    appendRangesFromAppointments(begin(appointments), itFirstTentative, ranges);
    int currentEnd = appendRangesFromAppointments(
        itFirstTentative, end(appointments), ranges);

    if (currentEnd != c_lastMinute)
    {
        ranges.push_back(
            Range {
                positionOfMinute(currentEnd),
                positionOfMinute(c_lastMinute),
                Pattern::Empty
            }
        );
    }

    return ranges;
}
