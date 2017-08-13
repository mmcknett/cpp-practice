#include <iostream>
#include "lru_cache.h"

void print(const LruCache& cache)
{
    auto cacheState = cache.getFullCache();
    std::cout << "Cache state:" << std::endl;
    for(std::pair<LruCache::TKey, LruCache::TValue>& it : cacheState)
    {
        std::cout << "\t" << it.first << ": " << it.second << std::endl;
    }
    std::cout << "\t[end]" << std::endl;
}

void set(LruCache& cache)
{
    std::cout << "Enter key then value, space separated positive ints:" << std::endl;
    LruCache::TKey key;
    LruCache::TValue value;
    std::cin >> key;
    std::cin >> value;
    cache.set(key, value);
}

void get(const LruCache& cache)
{
    std::cout << "Enter key to retrieve, positive int:" << std::endl;
    LruCache::TKey key;
    std::cin >> key;
    LruCache::TValue value = cache.get(key);
    std::cout << "==> ";
    if (value == LruCache::INVALID)
    {
        std::cout << "INVALID";
    }
    else
    {
        std::cout << value;
    }
    std::cout << std::endl;
}

enum class Command
{
    Set,
    Get,
    Print,
    Done,
    Unknown,
};

Command readCommand()
{
    std::string command;
    std::cout << "> ";
    std::cin >> command;

    if (command == "set")
    {
        return Command::Set;
    }
    else if(command == "get")
    {
        return Command::Get;
    }
    else if (command == "print")
    {
        return Command::Print;
    }
    else if (command == "done")
    {
        return Command::Done;
    }
    else
    {
        return Command::Unknown;
    }
}

void mainLoop(LruCache& cache)
{
    Command lastCommand;
    for(;;)
    {
        lastCommand = readCommand();
        switch(lastCommand)
        {
        case Command::Get:
            get(cache);
            break;
        case Command::Set:
            set(cache);
            break;
        case Command::Print:
            print(cache);
            break;
        case Command::Done:
            return;
        default:
            std::cout << "Sorry, say again?" << std::endl;
        }

        std::cout << std::endl;
    }
}

int main()
{
    std::cout << "Try out the LRU cache." << std::endl;
    std::cout << "First, enter LRU cache capacity (positive int > 0): ";

    unsigned int capacity;
    std::cin >> capacity;

    LruCache mainLruCache(capacity);

    std::cout << "Commands: set, get, print, done" << std::endl;

    mainLoop(mainLruCache);

    std::cout << "Final cache state..." << std::endl;
    print(mainLruCache);

    return 0;
}
