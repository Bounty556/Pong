#pragma once

#include <Defines.h>
#include <Core/Logger.h>

#include <new>

// Takes in the type of the object and calls its constructor
#define PARTITION(type, ...) (new (Soul::MemoryManager::PartitionMemory(sizeof(type))) type(__VA_ARGS__))

#define PARTITION_ARRAY(type, count) ((type*)(Soul::MemoryManager::PartitionMemory(sizeof(type), count)))

namespace Soul
{
	/*
	Memory Manager for the Soul engine. This works by creating a memory arena that
	can have memory partitioned in it from anywhere in the program.

	This first needs to be initialized by calling Initialize(), and must
	be cleaned up when the program closes via Shutdown().

	There are currently two ways to partition memory:
	
	1. Partitioning using the PARTITION macro, which will initialize the object in place of the
	   partitioned memory.

	2. Partitioning using the PARTITION_ARRAY macro. This will not initialize any of the objects
	   in the array, so care will need to be taken to initialize them manually.
	   Ex:
	   m_Controls = PARTITION_ARRAY(Input, 4); // Partition
	   for (unsigned int i = 0; i < 4; ++i)
	   {
	       new (m_Controls + i) Input(); // Initialize
	   }

	To free memory from the memory arena, call FreeMemory(). This will allow the
	space that variable took up to be marked as usable again. ALL MEMORY SHOULD
	BE FREED BEFORE DEALLOCATING THE MEMORY ARENA!!!!! (this does not include
	primitives)

	A side effect of using the MemoryManager is that there is an implicit way to
	keep track of the size of an array that was partitioned into the memory arena.
	Simply use the GetByteSize() function to find the byte length of the array
	partitioned, and then you can divide that by the size of the object/primitive
	partitioned to get the array size.
	*/
	class SOULAPI MemoryManager
	{
	private:
		/*
		Placed at the start of each block of free memory in our memory
		arena.
		*/
		struct MemoryNode
		{
			u32 BlockSize; // The size of the free memory block, including this node
			MemoryNode* NextNode; // Location of the following node in memory
		};

		/*
		Placed at the start of each partition to note how many bytes are stored.
		*/
		struct PartitionHeader
		{
			u32 Bytes; // The number of bytes stored in this partition, including header
			u32 Count; // The number of objects store in this partition
		};

	public:
		MemoryManager() = delete;

		/*
		Initializes our whole memory block.
		*/
		static bool Initialize(u32 bytes);

		/*
		Cleans up all allocated memory.
		*/
		static void Shutdown();

		/*
		Attempts to mark a block of free memory as used, and returns
		a pointer to the start of said used memory. This *can* return
		a block of memory that's slightly larger for formatting
		purposes. This will return nullptr if the partitioning failed.
		*/
		static void* PartitionMemory(u32 bytes, u32 count = 1);

		/*
		Marks the memory at the given location as unused and calls
		deconstructor on object.
		*/
		template<class T>
		static void FreeMemory(T* location);

		/*
		Because of the way that we store our variables in memory (with
		a small header for each one indicating their byte size) we get
		a free benefit in being able to tell the exact byte size of
		any allocated variable. Useful for not having to keep track of
		those pesky array sizes.
		*/
		static u32 GetByteSize(void* location);

		/*
		Returns the total number of bytes that are considered *used*
		within this memory arena.
		*/
		static u32 GetTotalPartitionedMemory();

		/*
		Returns the total number of bytes that are considered free
		within this memory arena.
		*/
		static u32 GetTotalFreeMemory();

		/*
		Draws a rough representation of memory to the console.
		*/
		static void DrawMemory();

	private:
		/*
		Walks the list of nodes, making sure all connections between
		nodes are up to date.
		*/
		static void RemoveNode(MemoryNode* removedNode);

		/*
		Walks the list of nodes, making sure all connections between
		nodes are up to date.
		*/
		static void AddNode(void* newLocation);

		/*
		Returns the number of memory nodes (free blocks) in our memory
		arena.
		*/
		static u32 CountNodes();

	private:
		static u8* m_AllocatedMemory; // Our entire allocated memory byte array
		static void* m_AllocMemoryStart; // The location of the start of our stable memory block
		static void* m_AllocMemoryEnd; // The location of the end of our stable memory block
		static bool m_MemoryInitialized;
	};

	template<class T>
	void MemoryManager::FreeMemory(T* location)
	{
		if (location == nullptr)
		{
			LOG_WARN("Nullptr was attempted to be freed.");
			return;
		}

		u8 testblock[fixedElementSize];
		memset(testblock, 0, sizeof testblock);

		if (!memcmp(testblock, memoryBlock + elementNr * fixedElementSize, fixedElementSize)

		// Check to see if this is an array we're freeing
		PartitionHeader* header = (PartitionHeader*)((u8*)location - sizeof(PartitionHeader));

		for (u32 i = 0; i < header->Count; ++i)
			location[i].~T();

		AddNode(location);
	}
}