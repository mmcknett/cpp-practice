#ifndef RANGEMAKER_H_INCLUDED
#define RANGEMAKER_H_INCLUDED

#include "appointment.h"
#include "range.h"
#include <vector>

class RangeMaker
{
public:
    RangeMaker(
        Pattern fillPattern,
        Ranges& ranges);

    int appendAppointments(
        std::vector<Appointment>::const_iterator itStartAppts,
        std::vector<Appointment>::const_iterator itEndAppts,
        int startTime,
        int endTime);

private:
    Range createRange(int startMinute, int endMinute, FreeBusy state);
    Range fillRange(int startMinute, int endMinute);
    Range createRange(int startMinute, int endMinute, Pattern pattern);

    void init(int startMinutes);
    void appendAppointmentsOnly(
        std::vector<Appointment>::const_iterator itStartAppts,
        std::vector<Appointment>::const_iterator itEndAppts);
    void fillLeftoverRange(int endMinutes);

    bool shouldIgnoreAppointment(const Appointment& appt);
    void addPaddingRangeIfNeeded(const Appointment& appt);
    int adjustStartForPreviouslyConsideredRange(const Appointment& appt);
    void appendRangeForAppointment(
        const Appointment& appt,
        std::vector<Appointment>::const_iterator itNextAppt,
        std::vector<Appointment>::const_iterator itEndAppts);
    bool shouldAppendSolidLayer(const Appointment& appt);

    void appendAppointmentsForNextLayer(
        const Appointment& currentAppointment,
        std::vector<Appointment>::const_iterator itNextAppt,
        std::vector<Appointment>::const_iterator itEndAppts,
        int startMinutes,
        Pattern nextLayerPattern);
    void appendRangeForAppointmentNow(
        const Appointment& appt,
        int startMinutes);

    Pattern _fillPattern;
    Ranges& _ranges;

    int _priorRangeEndMinutes;
};

#endif /* end of include guard: RANGEMAKER_H_INCLUDED */
