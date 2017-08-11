#include "adder.h"

intList Add(intList lhs, intList rhs)
{
    if (lhs.empty())
    {
        return rhs;
    }
    else if (rhs.empty())
    {
        return lhs;
    }

    // Add the two first digits together.
    unsigned int sum = lhs.front() + rhs.front();
    // lhs.pop_front();
    // rhs.pop_front();

    intList result;
    result.push_back(sum);

    return result;
}
