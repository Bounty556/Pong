#pragma once

#include <Defines.h>
#include <Memory/MemoryManager.h>
#include <Memory/UniquePointer.h>
#include <Math/Functions.h>
#include <Math/Hashes.h>
#include <Platform/Platform.h>
#include <Structures/Vector.h>

#define MapType Map<K, V>
#define SetType Set<K, V>

namespace Soul
{
	/*
	A dictionary-like structure implemented using a hash map. All keys must be
	hashable via an overloaded Hash function. The type stored in this Map
	should either be a primitive, or a type with a proper move constructor.
	*/
	template <class K, class V>
	class Map
	{
	public:
		template <class K, class V>
		struct Set
		{
			bool isInitialized;
			K key;
			V value;
		};

	public:
		Map(u32 capacity = 11);

		Map(const Map&) = delete;
		Map(Map&& otherMap) noexcept;

		~Map();
		
		Map& operator=(const Map&) = delete;
		Map& operator=(Map&& otherMap) noexcept;

		bool operator==(const Map& otherMap) const;

		bool AddPair(const K& key, const V& value);
		bool AddPair(const K& key, V&& value);
		bool AddPair(K&& key, const V& value);
		bool AddPair(K&& key, V&& value);

		void RemovePair(const K& key);
		void Clear();

		V* GetValue(const K& key) const;
		u32 Count() const;

		/*
		Returns a vector of all of the keys stored in this map.
		*/
		Vector<K*> GetKeys() const;

		/*
		Returns a vector of all of the values stored in this map.
		*/
		Vector<V*> GetValues() const;

	private:
		/*
		Returns the first found open location based on the key given. Returns
		-1 if none found.
		*/
		i64 FindOpenLocation(const K& key) const;
		/*
		Returns the location of the set that matches the provided key. Returns
		-1 if none found.
		*/
		i64 FindExistingLocation(const K& key) const;
		void Resize(u32 newCapacity);

	private:
		u32 m_Capacity; // Max capacity. Should be prime at all times
		u32 m_Size;
		UniquePointer<Set<K, V>> m_Map;
	};

	template <class K, class V>
	Map<K, V>::Map(u32 capacity) :
		m_Capacity(Math::FindNextPrime(capacity)),
		m_Size(0),
		m_Map(NEW_ARRAY(MapType::SetType, m_Capacity))
	{
	}

	template <class K, class V>
	Map<K, V>::Map(Map<K, V>&& otherMap) noexcept :
		m_Capacity(otherMap.m_Capacity),
		m_Size(otherMap.m_Size),
		m_Map(std::move(otherMap.m_Map))
	{
		otherMap.m_Capacity = 0;
		otherMap.m_Size = 0;
	}

	template <class K, class V>
	Map<K, V>::~Map()
	{
		// Call all destructors
		for (u32 i = 0; i < m_Capacity; ++i)
		{
			if (m_Map[i].isInitialized)
			{
				m_Map[i].key.~K();
				m_Map[i].value.~V();
			}
		}
	}

	template <class K, class V>
	Map<K, V>& Map<K, V>::operator=(Map<K, V>&& otherMap) noexcept
	{
		Clear();
		m_Capacity = otherMap.m_Capacity;
		m_Size = otherMap.m_Size;
		m_Map = std::move(otherMap.m_Map);
		otherMap.m_Capacity = 0;
		otherMap.m_Size = 0;

		return *this;
	}

	template <class K, class V>
	bool Map<K, V>::operator==(const Map<K, V>& otherMap) const
	{
		return (otherMap.m_Map.Raw() == m_Map.Raw());
	}

	template <class K, class V>
	bool Map<K, V>::AddPair(const K& key, const V& value)
	{
		// Check to make sure adding this doesn't fill our capacity
		if (m_Size + 1 >= (u32)(m_Capacity * .5f))
			Resize(Math::FindNextPrime(m_Capacity * 2));

		i64 openLocation = FindOpenLocation(key);

		if (openLocation == -1)
			return false;

		u32 location = (u32)openLocation;

		m_Map[location].isInitialized = true;
		new (&m_Map[location].key) K(key);
		new (&m_Map[location].value) V(value);
		
		m_Size++;

		return true;
	}

	template <class K, class V>
	bool Map<K, V>::AddPair(K&& key, V&& value)
	{
		// Check to make sure adding this doesn't fill our capacity
		if (m_Size + 1 >= (u32)(m_Capacity * .5f))
			Resize(Math::FindNextPrime(m_Capacity * 2));

		i64 openLocation = FindOpenLocation(key);

		if (openLocation == -1)
			return false;

		u32 location = (u32)openLocation;

		m_Map[location].isInitialized = true;
		new (&m_Map[location].key) K(std::move(key));
		new (&m_Map[location].value) V(std::move(value));

		m_Size++;

		return true;
	}

	template <class K, class V>
	bool Map<K, V>::AddPair(const K& key, V&& value)
	{
		// Check to make sure adding this doesn't fill our capacity
		if (m_Size + 1 >= (u32)(m_Capacity * .5f))
			Resize(Math::FindNextPrime(m_Capacity * 2));

		i64 openLocation = FindOpenLocation(key);

		if (openLocation == -1)
			return false;

		u32 location = (u32)openLocation;

		m_Map[location].isInitialized = true;
		new (&m_Map[location].key) K(key);
		new (&m_Map[location].value) V(std::move(value));

		m_Size++;

		return true;
	}
	
	template <class K, class V>
	bool Map<K, V>::AddPair(K&& key, const V& value)
	{
		// Check to make sure adding this doesn't fill our capacity
		if (m_Size + 1 >= (u32)(m_Capacity * .5f))
			Resize(Math::FindNextPrime(m_Capacity * 2));

		i64 openLocation = FindOpenLocation(key);

		if (openLocation == -1)
			return false;

		u32 location = (u32)openLocation;

		m_Map[location].isInitialized = true;
		new (&(m_Map[location].key)) K(std::move(key));
		new (&m_Map[location].value) V(value);

		m_Size++;

		return true;
	}

	template <class K, class V>
	void Map<K, V>::Clear()
	{
		// Call all destructors
		for (u32 i = 0; i < m_Capacity; ++i)
		{
			if (m_Map[i].isInitialized)
			{
				m_Map[i].key.~K();
				m_Map[i].value.~V();
			}
		}

		// Clear all data
		PlatformSetMemory(m_Map.Raw(), 0, m_Capacity * sizeof(Set<K, V>));
		m_Size = 0;
	}

	template <class K, class V>
	V* Map<K, V>::GetValue(const K& key) const
	{
		i64 existingLocation = FindExistingLocation(key);

		if (existingLocation == -1)
			return nullptr;

		u32 location = (u32)existingLocation;

		if (!m_Map[location].isInitialized)
			return nullptr;
		else
			return &m_Map[location].value;
	}

	template <class K, class V>
	u32 Map<K, V>::Count() const
	{
		return m_Size;
	}

	template <class K, class V>
	Vector<K*> Map<K, V>::GetKeys() const
	{
		Vector<K*> keys(m_Size);
		for (u32 i = 0; i < m_Capacity; ++i)
			if (m_Map[i].isInitialized)
				keys.Push(&m_Map[i].key);

		return keys;
	}

	template <class K, class V>
	Vector<V*> Map<K, V>::GetValues() const
	{
		Vector<V*> values(m_Size);
		for (u32 i = 0; i < m_Capacity; ++i)
			if (m_Map[i].isInitialized)
				values.Push(&m_Map[i].value);

		return values;
	}

	template <class K, class V>
	void Map<K, V>::RemovePair(const K& key)
	{
		i64 existingLocation = FindExistingLocation(key);

		if (existingLocation == -1)
			return;

		u32 location = (u32)existingLocation;

		// Assume we found the location where the pair resides
		m_Map[location].key.~K();
		m_Map[location].value.~V();
		PlatformSetMemory(&m_Map[location], 0, sizeof(Set<K, V>));
		m_Size--;
	}

	template <class K, class V>
	i64 Map<K, V>::FindOpenLocation(const K& key) const
	{
		// Find the location to place this pair
		u64 hash = Math::Hash(key);
		u32 location = hash % m_Capacity;

		u32 attempts = 0;
		u32 maxAttempts = m_Capacity / 2 + 1;
		// Check to see if there is an object at that location
		// TODO: store hash?
		while (m_Map[location].isInitialized && Math::Hash(m_Map[location].key) != hash)
		{
			// We couldn't find a spot
			if (attempts++ >= maxAttempts)
			{
				LOG_DEBUG("Could not find valid memory for new pair.\nCurrent capacity: %d\nCurrent pairs: %d",
					m_Capacity, m_Size);
				return -1;
			}

			location = (location + (attempts * attempts)) % m_Capacity;
		}

		return location;
	}

	template <class K, class V>
	i64 Map<K, V>::FindExistingLocation(const K& key) const
	{
		// Find the location to place this pair
		u64 hash = Math::Hash(key);
		u32 location = hash % m_Capacity;

		u32 attempts = 0;
		u32 maxAttempts = m_Capacity / 2 + 1;

		// Check to see if there is an object at that location
		while (m_Map[location].isInitialized && m_Map[location].key != key)
		{
			// We couldn't find a spot
			if (attempts++ >= maxAttempts)
			{
				LOG_DEBUG("Could not find value with hash: %lld", hash);
				return -1;
			}

			location = (location + (attempts * attempts)) % m_Capacity;
		}

		return location;
	}

	template <class K, class V>
	void Map<K, V>::Resize(u32 newCapacity)
	{
		// Create a new memory block with the necessary size, move all previous elements into it
		UniquePointer<Set<K, V>> newMemory(NEW_ARRAY(SetType, newCapacity));

		for (u32 i = 0; i < m_Capacity; ++i)
		{
			if (!m_Map[i].isInitialized)
				continue;

			// Find the location to place this pair
			auto key = m_Map[i].key;
			u64 hash = Math::Hash(m_Map[i].key);
			u32 location = hash % newCapacity;

			u32 attempts = 0;
			u32 maxAttempts = newCapacity / 2;
			// Check to see if there is an object at that location
			while (newMemory[location].isInitialized)
			{
				ASSERT(attempts++ < maxAttempts);

				location = (location + (attempts * attempts)) % newCapacity;
			}

			newMemory[location].isInitialized = true;
			new (&newMemory[location].key) K(std::move(m_Map[i].key));
			new (&newMemory[location].value) V(std::move(m_Map[i].value));
		}

		// Free the old memory and reassign
		m_Map = std::move(newMemory);
		m_Capacity = newCapacity;
	}
}