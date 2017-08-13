#ifndef LRU_CACHE_H_INCLUDED
#define LRU_CACHE_H_INCLUDED

#include <map>
#include <list>

class LruCache
{
public:
    typedef unsigned int TKey;
    typedef int TValue;

    const static TValue INVALID = -1;

    LruCache(unsigned int capacity);

    TValue get(TKey key);
    void set(TKey key, TValue value);

private:
    std::map<TKey, TValue> m_cache;
    std::list<TKey> m_mruList;
    unsigned int m_capacity;
};

#endif /* end of include guard: LRU_CACHE_H_INCLUDED */
