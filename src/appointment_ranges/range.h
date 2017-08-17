#ifndef RANGE_H_INCLUDED
#define RANGE_H_INCLUDED

#include <vector>

enum class Pattern
{
    Empty = 0,
    Hashed = 1,
    Solid = 2,
};

struct Range
{
    double yStart;
    double yEnd;
    Pattern pattern;
};

class Ranges
{
public:
    void addRange(Range&& range);
    const std::vector<Range>& getRanges() const;

private:
    std::vector<Range> ranges;
};

bool operator==(const Range& lhs, const Range& rhs);

#endif /* end of include guard: RANGE_H_INCLUDED */
