#ifndef RANGE_H_INCLUDED
#define RANGE_H_INCLUDED

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

inline bool operator==(const Range& lhs, const Range& rhs)
{
    return lhs.yStart == rhs.yStart &&
        lhs.yEnd == rhs.yEnd &&
        lhs.pattern == rhs.pattern;
}

#endif /* end of include guard: RANGE_H_INCLUDED */
