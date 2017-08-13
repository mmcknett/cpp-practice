#include <stdexcept>
#include "lru_cache.h"

LruCache::LruCache(unsigned int capacity)
    : m_mruHead(nullptr)
    , m_mruTail(nullptr)
    , m_capacity(capacity)
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
        ListNode* valueNode = m_cache.at(key);
        moveToFront(valueNode);
        return valueNode->value;
    }
    else
    {
        return INVALID;
    }
}

void LruCache::moveToFront(ListNode* valueNode) const
{
    removeFromList(valueNode);
    insertAtFront(valueNode);
}

void LruCache::removeFromList(ListNode* valueNode) const
{
    if (valueNode->prev != nullptr)
    {
        valueNode->prev->next = valueNode->next;
    }

    if (valueNode->next != nullptr)
    {
        valueNode->next->prev = valueNode->prev;
    }

    if (m_mruHead == valueNode)
    {
        m_mruHead = valueNode->next;
    }

    if (m_mruTail == valueNode)
    {
        m_mruTail = valueNode->prev;
    }
}

void LruCache::insertAtFront(ListNode* valueNode) const
{
    valueNode->next = m_mruHead;
    valueNode->prev = nullptr;

    if (m_mruHead != nullptr)
    {
        m_mruHead->prev = valueNode;
    }

    m_mruHead = valueNode;
}

void LruCache::set(LruCache::TKey key, LruCache::TValue value)
{
    if (m_cache.find(key) != std::end(m_cache))
    {
        ListNode* valueNode = m_cache.at(key);
        moveToFront(valueNode);
        valueNode->value = value;
    }
    else
    {
        ListNode* nodeToInsert = new ListNode;
        nodeToInsert->key = key;
        nodeToInsert->value = value;
        insertAtFront(nodeToInsert);
        if (m_cache.size() == 0)
        {
            m_mruTail = nodeToInsert;
        }

        m_cache[key] = nodeToInsert;
    }

    while (m_cache.size() > m_capacity)
    {
        m_cache.erase(m_mruTail->key);

        if (m_mruTail->prev != nullptr)
        {
            m_mruTail->prev->next = nullptr;
        }

        ListNode* removedNode = m_mruTail;
        m_mruTail = m_mruTail->prev;
        delete removedNode;
    }
}

std::vector<std::pair<LruCache::TKey, LruCache::TValue>> LruCache::getFullCache() const
{
    std::vector<std::pair<LruCache::TKey, LruCache::TValue>> result;
    for (ListNode* curr = m_mruHead; curr != nullptr; curr = curr->next)
    {
        result.push_back(std::pair<LruCache::TKey, LruCache::TValue>(curr->key, curr->value));
    }
    return result;
}
