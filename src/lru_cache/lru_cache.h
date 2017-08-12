#ifndef LRU_CACHE_H_INCLUDED
#define LRU_CACHE_H_INCLUDED

class LruCache
{
public:
    typedef unsigned int TKey;
    typedef int TValue;

    static TValue INVALID = -1;

    LruCache(unsigned int capacity);

    TValue get(TKey key);
    void set(TKey key, TValue value);
};

#endif /* end of include guard: LRU_CACHE_H_INCLUDED */
