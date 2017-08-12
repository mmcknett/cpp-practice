#ifndef ADDER_H_INCLUDED
#define ADDER_H_INCLUDED

#include <list>

typedef std::list<unsigned int> intList;

// Add two numbers together, represented as a list, where the lowest
// order digit is the first entry in the list.
intList Add(intList lhs, intList rhs);

#endif /* end of include guard: ADDER_H_INCLUDED */
