# cpp-practice

This repository contains some solutions to coding problems I found interesting
from http://www.programcreek.com/2012/11/top-10-algorithms-for-coding-interview/.

The solutions are written in C++ and depend on the
[Boost unit test framework](http://www.boost.org/doc/libs/1_35_0/libs/test/doc/components/utf/index.html)
for unit testing and [Meson](http://mesonbuild.com/) for building (Meson produces ninja build collateral).
I tried to follow a disciplined Test-Driven Development approach to the solutions.

## Adder
The ```adder``` folder has an implementation (with tests and interactive mode) for
an adder that takes a linked list of digits and returns the sum as a linked list.
The original problem statement is here: http://www.programcreek.com/2012/12/add-two-numbers/.
After writing my own solution, I also included a C++ port of the provided problem
solution, which required a hand-rolled doubly-linked-list node structure that could
be accessed from a map.

## LRU Cache
The ```lru_cache``` folder has an implementation with tests and interactive mode for a
"Least-Recently Used" cache.  The original problem statement is here:
http://www.codewalk.com/2012/04/least-recently-used-lru-cache-implementation-java.html.
I also include a C++ port of the provided problem solution, after trying my hand
at the implementation myself.
