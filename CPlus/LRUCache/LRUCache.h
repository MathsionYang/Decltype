#pragma once
#include <string>
#include <unordered_map>
#include "CPlus/Global.h"
namespace CPlus
{
	namespace Cache
	{
		template<typename Key, typename Value>
		class CPlusAPI LRUCache
		{
		public:
			LRUCache(int nCapacity, Value ErrValue);

			Value GetValue(Key key)
			{
				auto it = m_VMap.find(key);
				if (it != m_VMap.end())
				{
					Cache* cache = it->second;
					MoveCacheToHead(cache);
					return cache->value;
				}
				else
				{
					return m_ErrValue;
				}
			}
			void SetValue(Key key, Value value)
			{
				auto it = m_VMap.find(key);
				if (it != m_VMap.end())
				{
					Cache* cache = it->second;
					cache->value = value;
					MoveCacheToHead(cache);
				}
				else
				{
					if (m_nCapacity == m_VMap.size())
					{
						Cache cache = RemoveLastCache();
						m_VMap.erase(cache->key);
						cache->key = key;
						cache->value = value;
						CachePush(cache);
						m_VMap[key] = value;
					}
					else
					{
						Cache* cache = new Cache(key, value);
						CachePush(cache);
						m_VMap[key] = value;
					}
				}
			}

		private:
			struct Cache {
				Cache() = default;
				Cache(Key key, Value value) : key(key), value(value) {}
				Key key;
				Value value;
				Cache* prev;
				Cache* next;
			};
			void CachePush(Cache* cache)
			{
				cache->next = cacheHead.next;
				cacheHead.next = cache;
				cache->next->prev = cache;
				cache->prev = &cacheHead;
			}
			void CachePush(Key key, Value value)
			{
				auto cache = Cache(key, value);
				CachePush(cache);
			}
			void MoveCacheToHead(Cache* cache)
			{
				cache->prev->next = cache->next;
				cache->next->prev = cache->prev;
				CachePush(cache);
			}
			Cache* RemoveLastCache() {
				Cache* c = cacheTail.prev;
				cacheTail.prev = c->prev;
				c->prev->next = &cacheTail;
				return c;
			}
		private:
			Cache cacheHead;
			Cache cacheTail;
			Value m_ErrValue;
			int m_nCapacity;
			unordered_map<Key, Cache*> m_VMap;

		};

		template<typename Key, typename Value>
		inline LRUCache<Key, Value>::LRUCache(int nCapacity, Value ErrValue) :m_nCapacity(nCapacity), m_ErrValue(ErrValue)
		{
			cacheHead.next = &cacheTail;
			cacheTail.prev = &cacheHead;
		}

	}
}
