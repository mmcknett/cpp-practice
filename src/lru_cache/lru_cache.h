#ifndef LRU_CACHE_H_INCLUDED
#define LRU_CACHE_H_INCLUDED

#include <list>
#include <map>
#include <utility>
#include <vector>

class LruCache
{
public:
    typedef unsigned int TKey;
    typedef int TValue;

    const static TValue INVALID = -1;

    LruCache(unsigned int capacity);

    TValue get(TKey key) const;
    void set(TKey key, TValue value);

    std::vector<std::pair<TKey, TValue>> getFullCache() const;

private:
    std::map<TKey, TValue> m_cache;
    mutable std::list<TKey> m_mruList;
    unsigned int m_capacity;
};

#endif /* end of include guard: LRU_CACHE_H_INCLUDED */
