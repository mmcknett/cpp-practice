#include "range.h"
#include <iostream>

using namespace std;

bool operator==(const Range& lhs, const Range& rhs)
{
    return lhs.yStart == rhs.yStart &&
        lhs.yEnd == rhs.yEnd &&
        lhs.pattern == rhs.pattern;
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

void Ranges::print() const
{
    cerr << "Ranges:" << endl;
    for(const auto& rg : ranges)
    {
        cerr << "\tRg: " << rg.yStart << " to " << rg.yEnd << ": "
            << (rg.pattern == Pattern::Empty ? "empty" : (rg.pattern == Pattern::Solid ? "Solid" : "Hashed"))
            << endl;
    }
}
