#ifndef APPOINTMENT_H_INCLUDED
#define APPOINTMENT_H_INCLUDED

// Order matters for sorting.
enum class FreeBusy
{
    Busy = 0,
    Tentative = 1,
    Free = 2,
};

struct Appointment
{
    int startMinute;
    int endMinute;
    FreeBusy state;

    bool startsAfter(int minute) const;
    bool endsAfter(int minute) const;
};

bool operator<(const Appointment& lhs, const Appointment& rhs);

#endif /* end of include guard: APPOINTMENT_H_INCLUDED */
