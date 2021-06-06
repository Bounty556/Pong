#include "MemoryManager.h"

#include <Core/Logger.h>
#include <Platform/Platform.h>

namespace Soul
{
	u8* allocatedMemory; // Our entire allocated memory byte array
	void* allocMemoryStart; // The location of the start of our stable memory block
	void* allocMemoryEnd; // The location of the end of our stable memory block
	bool memoryInitialized = false;

	bool InitializeMemoryManager(u32 bytes)
	{
		allocatedMemory = (u8*)PlatformAllocateMemory(bytes);
		allocMemoryStart = allocatedMemory;
		allocMemoryEnd = allocatedMemory + bytes;

		// Create our 0th node at the start
		MemoryNode* memoryNode = (MemoryNode*)allocMemoryStart;
		memoryNode->BlockSize = bytes;
		memoryNode->NextNode = nullptr;

		memoryInitialized = true;

		return allocatedMemory;
	}

	void ShutdownMemoryManager()
	{
		PlatformFreeMemory(allocatedMemory);
	}

	void* PartitionMemory(u32 bytes, u32 count)
	{
		MemoryNode* currentNode = (MemoryNode*)allocMemoryStart;
		MemoryNode* smallestValidNode = nullptr;

		// Need more bytes to store the header for the partition we're making
		u32 actualBytes = (bytes * count) + sizeof(PartitionHeader); 

		while (currentNode)
		{
			// If this node is big enough to contain the partition and is smaller than the
			// smallest node already found, or if this node is big enough to contain the
			// partition and we have not found a node yet
			if (currentNode->BlockSize >= actualBytes)
			{
				if ((smallestValidNode && currentNode->BlockSize <= smallestValidNode->BlockSize) || !smallestValidNode)
				{
					smallestValidNode = currentNode;
				}
			}
			currentNode = currentNode->NextNode;
		}

		if (smallestValidNode)
		{
			// If we were to store memory here, can we keep our node?
			if (smallestValidNode->BlockSize - sizeof(MemoryNode) >= actualBytes)
			{
				void* location = ((u8*)smallestValidNode) + (smallestValidNode->BlockSize - actualBytes);

				// Initialize newly partitioned memory to 0
				PlatformSetMemory(location, 0, actualBytes);

				PartitionHeader* header = (PartitionHeader*)location;
				header->Bytes = actualBytes;
				header->Count = count;
				location = (u8*)location + sizeof(PartitionHeader);

				smallestValidNode->BlockSize -= actualBytes;

				return location;
			}
			// In this scenario, we can't keep our node - repair nodes afterwards
			else if (smallestValidNode->BlockSize >= actualBytes)
			{
				// If we try to remove our 0th node everything will break...
				Assert(smallestValidNode != allocMemoryStart);

				void* location = smallestValidNode;
				u32 blockSize = smallestValidNode->BlockSize;

				RemoveNode(smallestValidNode);
				PlatformSetMemory(location, 0, smallestValidNode->BlockSize);

				PartitionHeader* header = (PartitionHeader*)location;
				header->Bytes = blockSize;
				header->Count = count;
				location = (u8*)location + sizeof(PartitionHeader);

				return location;
			}
		}

		// We couldn't find a valid memory block
		DrawMemory();
		LOG_ERROR("Failed to allocate %d bytes.", bytes);
		Assert(false);
		return (void*)nullptr;
	}

	u32 GetByteSize(void* location)
	{
		Assert(location >= allocMemoryStart);
		Assert(location < allocMemoryEnd);

		// Back newLocation up to where we put the header
		PartitionHeader* header = (PartitionHeader*)((u8*)location - sizeof(PartitionHeader));
		return header->Bytes - sizeof(PartitionHeader);
	}

	u32 GetTotalPartitionedMemory()
	{
		u32 freeBytes = GetTotalFreeMemory();
		u32 partitionedBytes = (u32)allocMemoryEnd - (u32)allocMemoryStart - freeBytes;

		return partitionedBytes;
	}

	u32 GetTotalFreeMemory()
	{
		MemoryNode* currentNode = (MemoryNode*)allocMemoryStart;
		u32 freeBytes = currentNode->BlockSize;

		while (currentNode->NextNode)
		{
			currentNode = currentNode->NextNode;
			freeBytes += currentNode->BlockSize;
		}

		return freeBytes;
	}

	void DrawMemory()
	{
		LOG_INFO("%d bytes available, %d bytes used. There are %d nodes in memory.",
			GetTotalFreeMemory(), GetTotalPartitionedMemory(), CountNodes());
	}

	void RemoveNode(MemoryNode* removedNode)
	{
		MemoryNode* currentNode = (MemoryNode*)allocMemoryStart;

		while (currentNode->NextNode != nullptr)
		{
			if (currentNode->NextNode == removedNode)
				currentNode->NextNode = removedNode->NextNode;
			else
				currentNode = currentNode->NextNode;
		}
	}

	void AddNode(void* location)
	{
		// Back newLocation up to where we put the header
		void* newLocation = (u8*)location - sizeof(PartitionHeader);
		u32 size = ((PartitionHeader*)newLocation)->Bytes;

		// Create a new memory node at the given location
		MemoryNode* newNode = (MemoryNode*)newLocation;
		newNode->BlockSize = size;

		MemoryNode* previousNode = (MemoryNode*)allocMemoryStart;
		MemoryNode* currentNode = (MemoryNode*)allocMemoryStart;
		while (currentNode->NextNode)
		{
			currentNode = currentNode->NextNode;

			// We passed the new Node, reconstruct
			if (newNode < currentNode)
			{
				bool didCombine = false;
				// Check to see if newNode and currentNode can be combined
				if ((u8*)newNode + newNode->BlockSize == (u8*)currentNode)
				{
					newNode->BlockSize += currentNode->BlockSize;
					newNode->NextNode = currentNode->NextNode;
					previousNode->NextNode = newNode;
					didCombine = true;
				}

				// Check to see if previousNode and newNode can be combined
				if ((u8*)previousNode + previousNode->BlockSize == (u8*)newNode)
				{
					previousNode->BlockSize += newNode->BlockSize;
					if (didCombine)
					{
						previousNode->NextNode = newNode->NextNode;
					}
				}
				else
				{
					previousNode->NextNode = newNode;
					if (!didCombine)
					{
						newNode->NextNode = currentNode;
					}
				}
				return;
			}

			previousNode = currentNode;
		}

		// If we still haven't found this new node, it must be at the end
		if ((u8*)currentNode + currentNode->BlockSize == (u8*)newNode)
		{
			currentNode->BlockSize += newNode->BlockSize;
		}
		else
		{
			currentNode->NextNode = newNode;
			newNode->NextNode = nullptr;
		}
	}

	u32 CountNodes()
	{
		MemoryNode* currentNode = (MemoryNode*)allocMemoryStart;
		u32 nodeCount = 0;

		while (currentNode)
		{
			nodeCount++;
			currentNode = currentNode->NextNode;
		}

		return nodeCount;
	}
}