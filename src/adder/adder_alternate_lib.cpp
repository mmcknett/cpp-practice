#include "adder.h"

intList Add(const intList& lhs, const intList& rhs)
{
    intList result;
    int sum = 0;
    auto itLhs = std::begin(lhs);
    auto itRhs = std::begin(rhs);

    while(
        itLhs != std::end(lhs) ||
        itRhs != std::end(rhs))
    {
        if (itLhs != std::end(lhs))
        {
            sum += *itLhs;
            ++itLhs;
        }

        if (itRhs != std::end(rhs))
        {
            sum += *itRhs;
            ++itRhs;
        }

        result.push_back(sum % 10);
        sum /= 10;
    }

    if (sum == 1)
    {
        result.push_back(sum);
    }

    return result;
}
