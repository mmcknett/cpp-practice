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

vector<Range> getRangesFromAppointments(vector<Appointment>& appointments)
{
    vector<Range> ranges;

    removeFreeAppointments(appointments);

    if (appointments.size() == 0)
    {
        ranges.push_back(
            Range {
                positionOfMinute(0),
                positionOfMinute(c_lastMinute),
                Pattern::Empty
            }
        );
    }

    return ranges;
}
