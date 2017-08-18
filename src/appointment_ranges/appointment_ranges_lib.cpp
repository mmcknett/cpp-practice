#include "appointment_ranges.h"
#include "conversions.h"
#include "rangemaker.h"

using namespace std;

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
