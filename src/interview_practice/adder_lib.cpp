#include "adder.h"

#include <iostream>

unsigned int popNextDigit(intList& number)
{
    unsigned int digit;
    if (number.empty())
    {
        digit = 0;
    }
    else
    {
        digit = number.front();
        number.pop_front();
    }
    return digit;
}

intList Add(intList lhs, intList rhs)
{
    if (lhs.empty())
    {
        return rhs;
    }

    if (rhs.empty())
    {
        return lhs;
    }

    intList result;
    unsigned int carry = 0;

    while ((!lhs.empty() && !rhs.empty()) || carry > 0)
    {
        unsigned int lhsDigit = popNextDigit(lhs);
        unsigned int rhsDigit = popNextDigit(rhs);

        // TODO: Throw exception if either digit is not 0-9

        // Add the two first digits together.
        unsigned int sum = lhsDigit + rhsDigit + carry;
        carry = 0;

        if (sum >= 10)
        {
            carry = sum / 10;
            sum = sum % 10;
        }

        result.push_back(sum);
    }

    return result;
}
