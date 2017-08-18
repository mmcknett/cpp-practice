#include "appointment_ranges.h"
#include "conversions.h"
#include <iostream>
#include "rangemaker.h"

using namespace std;

void printAppointments(const vector<Appointment>& appointments);

vector<Range> getRangesFromAppointments(const vector<Appointment>& appointmentsIn)
{
    vector<Appointment> appointments(appointmentsIn);
    sort(begin(appointments), end(appointments));

    printAppointments(appointments);

    Ranges ranges;
    RangeMaker rangeMaker(
        Pattern::Empty /*fillPattern*/,
        ranges);

    rangeMaker.appendAppointments(
        begin(appointments),
        end(appointments),
        0 /*startTime*/,
        c_lastMinute /*endTime*/);

    ranges.print();

    return ranges.getRanges();
}

void printAppointments(const vector<Appointment>& appointments)
{
    cerr << "Appointments:" << endl;
    for(auto appt : appointments)
    {
        cerr << "\tAppt: " << appt.startMinute << " to " << appt.endMinute << ": "
            << (appt.state == FreeBusy::Free ? "Free" : (appt.state == FreeBusy::Busy ? "Busy" : "Tentative"))
            << endl;
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
