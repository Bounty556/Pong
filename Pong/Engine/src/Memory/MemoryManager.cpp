#include "MemoryManager.h"

#include <Core/Logger.h>
#include <Platform/Platform.h>

namespace Soul
{
	unsigned char* m_Memory; // Our entire allocated memory byte array
	void* m_StableMemoryStart; // The location of the start of our stable memory block
	void* m_StableMemoryEnd; // The location of the end of our stable memory block

	void InitializeMemoryManager(u32 bytes)
	{
		m_Memory = (unsigned char*)PlatformAllocateMemory(bytes);
		m_StableMemoryStart = m_Memory;
		m_StableMemoryEnd = m_Memory + bytes;

		// Create our 0th node at the 2MB mark
		MemoryNode* memoryNode = (MemoryNode*)m_StableMemoryStart;
		memoryNode->BlockSize = bytes; // - Megabytes(2);
		memoryNode->NextNode = nullptr;
	}

	void ShutdownMemoryManager()
	{
		PlatformFreeMemory(m_Memory);
	}

	void* PartitionMemory(unsigned int bytes, unsigned int count)
	{
		MemoryNode* currentNode = (MemoryNode*)m_StableMemoryStart;
		MemoryNode* smallestValidNode = nullptr;

		// Need more bytes to store the header for the partition we're making
		unsigned int actualBytes = (bytes * count) + sizeof(PartitionHeader); 

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
				void* location = ((unsigned char*)smallestValidNode) + (smallestValidNode->BlockSize - actualBytes);

				// Initialize newly partitioned memory to 0
				PlatformSetMemory(location, 0, actualBytes);

				PartitionHeader* header = (PartitionHeader*)location;
				header->Bytes = actualBytes;
				header->Count = count;
				location = (unsigned char*)location + sizeof(PartitionHeader);

				smallestValidNode->BlockSize -= actualBytes;

				return location;
			}
			// In this scenario, we can't keep our node - repair nodes afterwards
			else if (smallestValidNode->BlockSize >= actualBytes)
			{
				// If we try to remove our 0th node everything will break...
				Assert(smallestValidNode != m_StableMemoryStart);

				void* location = smallestValidNode;
				unsigned int blockSize = smallestValidNode->BlockSize;

				RemoveNode(smallestValidNode);
				PlatformSetMemory(location, 0, smallestValidNode->BlockSize);

				PartitionHeader* header = (PartitionHeader*)location;
				header->Bytes = blockSize;
				header->Count = count;
				location = (unsigned char*)location + sizeof(PartitionHeader);

				return location;
			}
		}

		// We couldn't find a valid memory block
		DrawMemory();
		LOG_ERROR("Failed to allocate %d bytes.", bytes);
		Assert(false);
		return (void*)nullptr;
	}

	unsigned int GetByteSize(void* location)
	{
		Assert(location >= m_StableMemoryStart);
		Assert(location < m_StableMemoryEnd);

		// Back newLocation up to where we put the header
		PartitionHeader* header = (PartitionHeader*)((unsigned char*)location - sizeof(PartitionHeader));
		return header->Bytes - sizeof(PartitionHeader);
	}

	u32 GetTotalPartitionedMemory()
	{
		unsigned int freeBytes = GetTotalFreeMemory();
		unsigned int partitionedBytes = (unsigned int)m_StableMemoryEnd - (unsigned int)m_StableMemoryStart - freeBytes;

		return partitionedBytes;
	}

	u32 GetTotalFreeMemory()
	{
		MemoryNode* currentNode = (MemoryNode*)m_StableMemoryStart;
		unsigned int freeBytes = currentNode->BlockSize;

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
		MemoryNode* currentNode = (MemoryNode*)m_StableMemoryStart;

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
		void* newLocation = (unsigned char*)location - sizeof(PartitionHeader);
		unsigned int size = ((PartitionHeader*)newLocation)->Bytes;

		// Create a new memory node at the given location
		MemoryNode* newNode = (MemoryNode*)newLocation;
		newNode->BlockSize = size;

		MemoryNode* previousNode = (MemoryNode*)m_StableMemoryStart;
		MemoryNode* currentNode = (MemoryNode*)m_StableMemoryStart;
		while (currentNode->NextNode)
		{
			currentNode = currentNode->NextNode;

			// We passed the new Node, reconstruct
			if (newNode < currentNode)
			{
				bool didCombine = false;
				// Check to see if newNode and currentNode can be combined
				if ((unsigned char*)newNode + newNode->BlockSize == (unsigned char*)currentNode)
				{
					newNode->BlockSize += currentNode->BlockSize;
					newNode->NextNode = currentNode->NextNode;
					previousNode->NextNode = newNode;
					didCombine = true;
				}

				// Check to see if previousNode and newNode can be combined
				if ((unsigned char*)previousNode + previousNode->BlockSize == (unsigned char*)newNode)
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
		if ((unsigned char*)currentNode + currentNode->BlockSize == (unsigned char*)newNode)
		{
			currentNode->BlockSize += newNode->BlockSize;
		}
		else
		{
			currentNode->NextNode = newNode;
			newNode->NextNode = nullptr;
		}
	}

	unsigned int CountNodes()
	{
		MemoryNode* currentNode = (MemoryNode*)m_StableMemoryStart;
		unsigned int nodeCount = 0;

		while (currentNode)
		{
			nodeCount++;
			currentNode = currentNode->NextNode;
		}

		return nodeCount;
	}
}