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

    Pattern _fillPattern;
    Ranges& _ranges;

    int priorRangeEndMinutes;
};

RangeMaker::RangeMaker(
    Pattern fillPattern,
    Ranges& ranges)
    : _fillPattern(fillPattern)
    , _ranges(ranges)
    , priorRangeEndMinutes(0)
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

    return priorRangeEndMinutes;
}

void RangeMaker::init(int startMinutes)
{
    priorRangeEndMinutes = startMinutes;
}

void RangeMaker::appendAppointmentsOnly(
    vector<Appointment>::const_iterator itStartAppts,
    vector<Appointment>::const_iterator itEndAppts)
{
    for(auto itCurr = itStartAppts; itCurr != itEndAppts; ++itCurr)
    {
        const Appointment& appt = *itCurr;

        if (appt.state == FreeBusy::Free ||
            !appt.endsAfter(priorRangeEndMinutes))
        {
            // Ignore free appointments and appointments that don't
            // end after the range we've already considered.
            continue;
        }

        bool spacingRequired = appt.startsAfter(priorRangeEndMinutes);

        // Add an empty range if there is space between the last end and this start.
        if (spacingRequired)
        {
            _ranges.addRange(
                fillRange(priorRangeEndMinutes, appt.startMinute));
        }

        // Use the prior end or the current start, whichever is later.
        int adjustedStart = std::max(priorRangeEndMinutes, appt.startMinute);
        if (appt.state == FreeBusy::Tentative)
        {
            auto itNextNonOverlappingAppt =
                find_if(itCurr, itEndAppts,
                    [&appt](const Appointment& other) { return other.startMinute >= appt.endMinute; });

            RangeMaker innerRangeMaker(
                Pattern::Hashed,
                _ranges);

            priorRangeEndMinutes = innerRangeMaker.appendAppointments(
                next(itCurr, 1),
                itNextNonOverlappingAppt,
                adjustedStart,
                appt.endMinute);
        }
        else
        {
            if (appt.endMinute - adjustedStart > 0)
            {
                _ranges.addRange(
                    createRange(adjustedStart, appt.endMinute, appt.state));

                priorRangeEndMinutes = appt.endMinute;
            }
        }
    }
}

void RangeMaker::fillLeftoverRange(int endMinutes)
{
    if (priorRangeEndMinutes < endMinutes)
    {
        _ranges.addRange(
            fillRange(priorRangeEndMinutes, endMinutes));

        priorRangeEndMinutes = endMinutes;
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
