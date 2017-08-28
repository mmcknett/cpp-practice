#include <iostream>
#include "mergesort.h"

std::vector<int> readStdInForInts();
void print(const std::vector<int>& ints);

int main()
{
    // Run merge sort on standard input.
    auto ints = readStdInForInts();
    mergeSort(ints);
    print(ints);
    std::cout << std::endl;

    return 0;
}

std::vector<int> readStdInForInts()
{
    std::vector<int> inputToSort;

    int lastInt;
    while(std::cin >> lastInt)
    {
        inputToSort.push_back(lastInt);
    }

    return inputToSort;
}

void print(const std::vector<int>& ints)
{
    for (auto it = std::begin(ints); it != std::end(ints); ++it)
    {
        std::cout << *it << (std::next(it, 1) == std::end(ints) ? "" : " ");
    }
}
