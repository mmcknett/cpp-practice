#include <iostream>
#include "mergesort.h"

std::vector<float> readStdInForFloats();
void print(const std::vector<float>& floats);

int main()
{
    // Run merge sort on standard input.
    auto floats = readStdInForFloats();
    mergeSort(floats);
    print(floats);
    std::cout << std::endl;

    return 0;
}

std::vector<float> readStdInForFloats()
{
    std::vector<float> inputToSort;

    float lastInt;
    while(std::cin >> lastInt)
    {
        inputToSort.push_back(lastInt);
    }

    return inputToSort;
}

void print(const std::vector<float>& floats)
{
    for (auto it = std::begin(floats); it != std::end(floats); ++it)
    {
        std::cout << *it << (std::next(it, 1) == std::end(floats) ? "" : " ");
    }
}
