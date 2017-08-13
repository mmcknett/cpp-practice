#ifndef LRU_CACHE_H_INCLUDED
#define LRU_CACHE_H_INCLUDED

#include <unordered_map>
#include <utility>
#include <vector>

struct ListNode;

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
    void moveToFront(ListNode* valueNode) const;
    void removeFromList(ListNode* valueNode) const;
    void insertAtFront(ListNode* valueNode) const;

    std::unordered_map<TKey, ListNode*> m_cache;
    mutable ListNode* m_mruHead;
    mutable ListNode* m_mruTail;
    unsigned int m_capacity;
};

struct ListNode
{
    ListNode* prev;
    ListNode* next;
    LruCache::TKey key;
    LruCache::TValue value;
};

#endif /* end of include guard: LRU_CACHE_H_INCLUDED */
