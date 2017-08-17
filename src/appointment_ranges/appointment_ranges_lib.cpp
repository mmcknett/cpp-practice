#include "appointment_ranges.h"

using namespace std;

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

vector<Range> getRangesFromAppointments(vector<Appointment>& appointments)
{
    vector<Range> ranges;

    removeFreeAppointments(appointments);

    // Assume the appointments are sorted, busy first, then tentative,
    // lowest minutes first.

    // TODO: Do a pass per non-Free FreeBusy state.

    int currentEnd = 0;
    for (auto& appt : appointments)
    {
        // Ignore anything that ends prior to or at the end of the previous window,
        // since anything before now takes precedence.
        if (appt.endMinute > currentEnd)
        {
            // Add an empty range if there is space between the last end and this start.
            if (appt.startMinute > currentEnd)
            {
                ranges.push_back( Range{ positionOfMinute(currentEnd), positionOfMinute(appt.startMinute), Pattern::Empty });
            }

            // Use the prior end or the current start, whichever is later.
            int adjustedStart = std::max(currentEnd, appt.startMinute);

            // Use this range if it's non-zero.
            if (appt.endMinute - adjustedStart > 0)
            {
                ranges.push_back( Range{ positionOfMinute(adjustedStart), positionOfMinute(appt.endMinute), getPatternFromState(appt.state)});
            }

            currentEnd = appt.endMinute;
        }
    }

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
