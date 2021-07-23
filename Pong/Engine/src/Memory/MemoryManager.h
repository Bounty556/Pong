#pragma once

#include <Defines.h>
#include <Core/Logger.h>

#include <new>

#define NEW(type, ...) (new (Soul::MemoryManager::Partition(sizeof(type))) type(__VA_ARGS__))
#define NEW_ARRAY(type, count) ((type*)(Soul::MemoryManager::Partition(sizeof(type), count, true)))

namespace Soul
{
	/*
	Memory Manager for the Soul engine. This works by creating a memory arena
	that can have memory partitioned in it from anywhere in the program.

	This first needs to be initialized by calling Initialize(), and must be
	cleaned up when the program closes via Shutdown().

	There are currently two ways to partition memory:
	
	1. Partitioning using the NEW macro, which will initialize the object
	   in place of the partitioned memory.

	2. Partitioning using the NEW_ARRAY macro. This will not initialize
	   any of the objects in the array, so care will need to be taken to
	   initialize them manually. The same goes for deallocating the array.
	   Ex:
	   m_Controls = NEW_ARRAY(Input, 4); // Partition
	   for (u32 i = 0; i < 4; ++i)
	       new (m_Controls + i) Input(); // Initialize
	*/
	class SOULAPI MemoryManager
	{
	private:
		struct MemoryBlock
		{
			u32 blockSize;
			MemoryBlock* nextBlock;
			MemoryBlock* prevBlock;
			bool isArray;
			bool isAllocated;
		};

	public:
		MemoryManager() = delete;

		static bool Initialize(u32 bytes);
		static void Shutdown();

		/*
		Returns the address to the first block large enough to accommodate
		requested memory. Returns nullptr if unable to find any.
		*/
		static void* Partition(u32 bytes, u32 count = 1, bool isArray = false);

		/*
		Frees the memory at the given locatoin.
		*/
		template<class T>
		static void FreeMemory(T* location);

		/*
		Get the size of the memory allocation, assuming the location has a
		valid partition header
		*/
		static u32 GetByteSize(void* location);

		/*
		Returns the total number of bytes partitioned in the memory arena.
		*/
		static u32 GetTotalPartitionedMemory();

		/*
		Returns the total number of free bytes in the memory arena.
		*/
		static u32 GetTotalFreeMemory();

	private:
		/*
		Finds the first free block that is atleast of the provided size in
		bytes.
		*/
		static MemoryBlock* FindFreeBlockOfSize(u32 bytes);

		/*
		Sets the variables of the MemoryBlock at the location given, and sets
		up a new free memory block where it can.
		*/
		static void ConfigureMemoryBlocks(MemoryBlock* location, u32 bytes);

		/*
		Marks the memory block as free.
		*/
		static void FreeMemoryBlock(MemoryBlock* location);

		/*
		Combines consecutive free memory block together.
		*/
		static void CombineFreeBlocks(MemoryBlock* location);

	private:
		static u8* m_AllocatedMemory; // Our entire allocated memory byte array
		static void* m_AllocMemoryStart; // The location of the start of our stable memory block
		static void* m_AllocMemoryEnd; // The location of the end of our stable memory block
		static MemoryBlock* m_LastAllocBlock; // Last block of memory allocated or freed
		static bool m_IsInitialized;
	};

	template<class T>
	void MemoryManager::FreeMemory(T* location)
	{
		if (location == nullptr)
		{
			LOG_WARN("Nullptr was attempted to be freed.");
			return;
		}

		MemoryBlock* block = (MemoryBlock*)((u8*)location - sizeof(MemoryBlock));

		if (!header->isArray)
			location->~T();

		FreeMemoryBlock(block);
	}
}