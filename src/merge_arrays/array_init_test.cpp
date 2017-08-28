#include <iostream>
#include <vector>

void print(float* arrayStart, float* arrayEnd, unsigned int stride = 0)
{
    if (stride == 0)
    {
        std::cout << "Array: [";
    }
    else
    {
        std:: cout << "Matrix:" << std::endl;
    }

    for (float* it = arrayStart; it != arrayEnd; ++it)
    {
        std::cout << *it << (it + 1 == arrayEnd ? "" : " ");

        if (stride != 0 &&
            static_cast<unsigned int>(it - arrayStart + 1) % stride == 0 &&
            it + 1 != arrayEnd)
        {
            std::cout << std::endl;
        }
    }
    std::cout << (stride == 0 ? "]" : "") << std::endl;
}

void print(float* jaggedStart[], float* jaggedEnd[], size_t* sizes)
{
    std::cout << "Jagged array: [" << std::endl;

    for (float** itArray = jaggedStart; itArray != jaggedEnd; ++itArray, ++sizes)
    {
        std::cout << "[";
        float* arrayEnd = *itArray + *sizes;
        for (float* it = *itArray; it < *itArray + *sizes; ++it)
        {
            std::cout << *it << (it + 1 == arrayEnd ? "" : " ");
        }
        std::cout << "]" << std::endl;
    }
    std::cout << "]" << std::endl;
}

template <typename T>
void print(const std::vector<std::vector<T>>& jaggedVector)
{
    std::cout << "Vector: [" << std::endl;
    for (auto& vector : jaggedVector)
    {
        std::cout << "[";
        for (auto it = std::begin(vector); it != std::end(vector); ++it)
        {
            std::cout << *it << (std::next(it, 1) == std::end(vector) ? "" : " ");
        }
        std::cout << "]" << std::endl;
    }
    std::cout << "]" << std::endl;
}

int main()
{
    // Print a single decimal point for each floating point #.
    std::cout.precision(1);
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cout << std::endl;


    // C++ can infer the size from the initializer.
    float array[] = {1.0f, 2.0f, 4.5f, 5.0f};
    print(array, array + 4);

    std::cout << std::endl;


    // But C++ cannot infer the size for a two-dimensional array.
    // float matrix[][] = {  <-- produces an error because of the incomplete type 'float []'
    // Instead, you need to specify the size of the rows:
    float matrix[][3] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };
    float* pMatrix = &matrix[0][0];
    print(pMatrix, pMatrix + 9, 3);

    std::cout << std::endl;


    // You can initialize a jagged array, as long as the row length is
    // large enough to contain each element...
    float jaggedArray[][5] = {
        {1.0f, 2.0f},
        {3.5f, 4.5f, 5.5f, 6.5f, 7.0f/*, 8.0f <-- not this one; too many!*/},
        {},
        {4.0f}
    };
    // ...but it isn't a true jagged array.  You still allocate space for all
    // of the values you didn't initialize.  E.g. the 12 zeroes in 'jaggedArray'
    // will get printed below...
    pMatrix = &jaggedArray[0][0];
    print(pMatrix, pMatrix + 20, 5);

    std::cout << std::endl;


    // A true jagged array has to be an array of anonymous arrays created on the heap:
    float *realJaggedArray[] = {
        new float[2] {1.0f, 2.0f},
        new float[5] {3.5f, 4.5f, 5.5f, 6.5f, 7.0f},
        new float[0] {},
        new float[1] {4.0f}
    };
    size_t sizes[] = {2, 5, 0, 1}; // Note, you're going to need the sizes stored somewhere.
    print(realJaggedArray, realJaggedArray + 4, sizes);

    // And of course, you can't forget to delete the arrays!
    for (float** itArray = realJaggedArray; itArray < realJaggedArray + 4; ++itArray)
    {
        delete[] *itArray;
    }

    std::cout << std::endl;


    // At that point, it's much easier -- and safer! -- to use vectors:
    std::vector<std::vector<float>> jaggedVector = {
        {1.0f, 2.0f},
        {3.5f, 4.5f, 5.5f, 6.5f, 7.0f},
        {},
        {4.0f}
    };
    print(jaggedVector);

    std::cout << std::endl;


    return 0;
}
