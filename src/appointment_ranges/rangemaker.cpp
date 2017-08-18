#include "conversions.h"
#include "rangemaker.h"

using namespace std;

RangeMaker::RangeMaker(
    Pattern fillPattern,
    Ranges& ranges)
    : _fillPattern(fillPattern)
    , _ranges(ranges)
    , _priorRangeEndMinutes(0)
{
}

int RangeMaker::appendAppointments(
    vector<Appointment>::const_iterator itStartAppts,
    vector<Appointment>::const_iterator itEndAppts,
    int startTime,
    int endTime)
{
    init(startTime);

    appendAppointmentsOnly(
        itStartAppts,
        itEndAppts);

    fillLeftoverRange(endTime);

    return _priorRangeEndMinutes;
}

void RangeMaker::init(int startMinutes)
{
    _priorRangeEndMinutes = startMinutes;
}

void RangeMaker::appendAppointmentsOnly(
    vector<Appointment>::const_iterator itStartAppts,
    vector<Appointment>::const_iterator itEndAppts)
{
    for(auto itCurr = itStartAppts; itCurr != itEndAppts; ++itCurr)
    {
        const Appointment& appt = *itCurr;
        if (!shouldIgnoreAppointment(appt))
        {
            addPaddingRangeIfNeeded(appt);
            appendRangeForAppointment(appt, next(itCurr, 1), itEndAppts);
        }
    }
}

bool RangeMaker::shouldIgnoreAppointment(const Appointment& appt)
{
    // Ignore free appointments and appointments that don't
    // end after the range we've already considered.
    return appt.state == FreeBusy::Free ||
        !appt.endsAfter(_priorRangeEndMinutes);
}

void RangeMaker::addPaddingRangeIfNeeded(const Appointment& appt)
{
    bool spacingRequired = appt.startsAfter(_priorRangeEndMinutes);
    if (spacingRequired)
    {
        _ranges.addRange(
            fillRange(_priorRangeEndMinutes, appt.startMinute));
    }
}

void RangeMaker::appendRangeForAppointment(
    const Appointment& appt,
    vector<Appointment>::const_iterator itNextAppt,
    vector<Appointment>::const_iterator itEndAppts)
{
    int adjustedStart = adjustStartForPreviouslyConsideredRange(appt);
    if (shouldAppendSolidLayer(appt))
    {
        appendAppointmentsForNextLayer(
            appt,
            itNextAppt,
            itEndAppts,
            adjustedStart,
            Pattern::Hashed);
    }
    else
    {
        appendRangeForAppointmentNow(
            appt,
            adjustedStart);
    }
}

int RangeMaker::adjustStartForPreviouslyConsideredRange(const Appointment& appt)
{
    return std::max(_priorRangeEndMinutes, appt.startMinute);
}

bool RangeMaker::shouldAppendSolidLayer(const Appointment& appt)
{
    return (appt.state == FreeBusy::Tentative);
}

void RangeMaker::appendAppointmentsForNextLayer(
    const Appointment& currentAppointment,
    vector<Appointment>::const_iterator itNextAppt,
    vector<Appointment>::const_iterator itEndAppts,
    int startMinutes,
    Pattern nextLayerPattern)
{
    auto itNextNonOverlappingAppt =
        find_if(itNextAppt, itEndAppts,
            [&currentAppointment](const Appointment& other)
            {
                return other.startMinute >= currentAppointment.endMinute;
            }
        );

    RangeMaker innerRangeMaker(
        nextLayerPattern,
        _ranges);

    _priorRangeEndMinutes = innerRangeMaker.appendAppointments(
        itNextAppt,
        itNextNonOverlappingAppt,
        startMinutes,
        currentAppointment.endMinute);
}

void RangeMaker::appendRangeForAppointmentNow(
    const Appointment& appt,
    int startMinutes)
{
    if (appt.endMinute - startMinutes > 0)
    {
        _ranges.addRange(
            createRange(startMinutes, appt.endMinute, appt.state));

        _priorRangeEndMinutes = appt.endMinute;
    }
}

void RangeMaker::fillLeftoverRange(int endMinutes)
{
    if (_priorRangeEndMinutes < endMinutes)
    {
        _ranges.addRange(
            fillRange(_priorRangeEndMinutes, endMinutes));

        _priorRangeEndMinutes = endMinutes;
    }
}

Range RangeMaker::createRange(int startMinute, int endMinute, FreeBusy state)
{
    Pattern patternFromState = getPatternFromState(state);
    return createRange(startMinute, endMinute, patternFromState);
}

Range RangeMaker::fillRange(int startMinute, int endMinute)
{
    return createRange(startMinute, endMinute, _fillPattern);
}

Range RangeMaker::createRange(int startMinute, int endMinute, Pattern pattern)
{
    return Range {
        positionOfMinute(startMinute),
        positionOfMinute(endMinute),
        pattern
    };
}
