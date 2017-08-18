#ifndef APPOINTMENT_RANGES_INCLUDED
#define APPOINTMENT_RANGES_INCLUDED

#include "appointment.h"
#include "range.h"
#include <vector>

std::vector<Range> getRangesFromAppointments(const std::vector<Appointment>& appointments);

#endif /* end of include guard: APPOINTMENT_RANGES_INCLUDED */
