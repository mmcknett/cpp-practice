#ifndef CONVERSION_H_INCLUDED
#define CONVERSION_H_INCLUDED

#include "appointment.h"
#include "range.h"

const int c_lastMinute = 24 * 60;

Pattern getPatternFromState(FreeBusy state);
double positionOfMinute(int minute);

#endif /* end of include guard: CONVERSION_H_INCLUDED */
