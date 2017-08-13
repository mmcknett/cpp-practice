#include <stdexcept>
#include "lru_cache.h"

LruCache::LruCache(unsigned int capacity)
    : m_capacity(capacity)
{
    if (m_capacity < 1)
    {
        throw std::invalid_argument("Capacity must be more than 1.");
    }
}

LruCache::TValue LruCache::get(LruCache::TKey key) const
{
    if (m_cache.find(key) != std::end(m_cache))
    {
        auto itKeyInMruList = std::find(std::begin(m_mruList), std::end(m_mruList), key);
        if (itKeyInMruList != std::end(m_mruList))
        {
            m_mruList.erase(itKeyInMruList);
        }
        m_mruList.push_back(key);

        return m_cache.at(key);
    }
    else
    {
        return INVALID;
    }
}

void LruCache::set(LruCache::TKey key, LruCache::TValue value)
{
    // If the key is in the most-recently-used list already, remove it and
    // we'll re-add it.  Otherwise, remove the least-recently-used element.
    auto itKeyInMruList = std::find(std::begin(m_mruList), std::end(m_mruList), key);
    if (itKeyInMruList != std::end(m_mruList))
    {
        m_mruList.erase(itKeyInMruList);
    }
    else if(m_mruList.size() >= m_capacity)
    {
        m_cache.erase(m_mruList.front());
        m_mruList.pop_front();
    }

    m_cache[key] = value;
    m_mruList.push_back(key);
}

std::vector<std::pair<LruCache::TKey, LruCache::TValue>> LruCache::getFullCache() const
{
    std::vector<std::pair<LruCache::TKey, LruCache::TValue>> result;
    std::copy(std::begin(m_cache), std::end(m_cache), std::back_inserter(result));
    return result;
}
