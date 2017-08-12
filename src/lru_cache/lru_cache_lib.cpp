#include <stdexcept>
#include "lru_cache.h"

LruCache::LruCache(unsigned int capacity)
{
    if (capacity < 1)
    {
        throw std::invalid_argument("Capacity must be more than 1.");
    }
}
