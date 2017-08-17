#ifndef APPOINTMENT_RANGES_INCLUDED
#define APPOINTMENT_RANGES_INCLUDED

#include "appointment.h"
#include "range.h"
#include <vector>

const int c_lastMinute = 24 * 60;

std::vector<Range> getRangesFromAppointments(const std::vector<Appointment>& appointments);

Pattern getPatternFromState(FreeBusy state);
double positionOfMinute(int minute);

#endif /* end of include guard: APPOINTMENT_RANGES_INCLUDED */
