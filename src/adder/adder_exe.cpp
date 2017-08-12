#include "adder.h"
#include <iostream>

void printList(const intList& number)
{
    std::cout << "{";
    for (auto& digit : number)
    {
        std::cout << digit << ",";
    }
    std::cout << "}" << std::endl;
}

intList makeListFromInt(unsigned int i)
{
    intList result;
    while(i != 0)
    {
        result.push_back(i % 10);
        i /= 10;
    }

    return result;
}

unsigned int makeIntFromList(intList value)
{
    unsigned int multFactor = 1;
    unsigned int result = 0;
    while(!value.empty())
    {
        result += multFactor * value.front();
        value.pop_front();
        multFactor *= 10;
    }

    return result;
}

int main(int argc, char* argv[])
{
    // Default to using the adder
    // Assume we're given two unsigned integers.
    if (argc < 3)
    {
        return 1;
    }

    unsigned int lhs = std::stoul(argv[1]);
    unsigned int rhs = std::stoul(argv[2]);

    intList lhsList = makeListFromInt(lhs);
    intList rhsList = makeListFromInt(rhs);
    intList resultList = Add(lhsList, rhsList);

    unsigned int result = makeIntFromList(resultList);
    std::cout << result << std::endl;

    return 0;
}
