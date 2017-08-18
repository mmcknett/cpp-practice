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

class RangeMaker
{
public:
    RangeMaker(
        Pattern fillPattern,
        Ranges& ranges);

    int appendAppointments(
        vector<Appointment>::const_iterator itStartAppts,
        vector<Appointment>::const_iterator itEndAppts,
        int startTime,
        int endTime);

private:
    Range createRange(int startMinute, int endMinute, FreeBusy state);
    Range fillRange(int startMinute, int endMinute);
    Range createRange(int startMinute, int endMinute, Pattern pattern);

    void init(int startMinutes);
    void appendAppointmentsOnly(
        vector<Appointment>::const_iterator itStartAppts,
        vector<Appointment>::const_iterator itEndAppts);
    void fillLeftoverRange(int endMinutes);

    bool shouldIgnoreAppointment(const Appointment& appt);
    void addPaddingRangeIfNeeded(const Appointment& appt);
    int adjustStartForPreviouslyConsideredRange(const Appointment& appt);
    void appendRangeForAppointment(
        const Appointment& appt,
        vector<Appointment>::const_iterator itNextAppt,
        vector<Appointment>::const_iterator itEndAppts);
    bool shouldAppendSolidLayer(const Appointment& appt);

    void appendAppointmentsForNextLayer(
        const Appointment& currentAppointment,
        vector<Appointment>::const_iterator itNextAppt,
        vector<Appointment>::const_iterator itEndAppts,
        int startMinutes,
        Pattern nextLayerPattern);
    void appendRangeForAppointmentNow(
        const Appointment& appt,
        int startMinutes);

    Pattern _fillPattern;
    Ranges& _ranges;

    int _priorRangeEndMinutes;
};

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
