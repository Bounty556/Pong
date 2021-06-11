#include "MemoryManager.h"

#include <Core/Logger.h>
#include <Platform/Platform.h>

namespace Soul
{
	u8* MemoryManager::m_AllocatedMemory;
	void* MemoryManager::m_AllocMemoryStart;
	void* MemoryManager::m_AllocMemoryEnd;
	bool MemoryManager::m_MemoryInitialized = false;

	bool MemoryManager::Initialize(u32 bytes)
	{
		m_AllocatedMemory = (u8*)PlatformAllocateMemory(bytes);
		m_AllocMemoryStart = m_AllocatedMemory;
		m_AllocMemoryEnd = m_AllocatedMemory + bytes;

		// Create our 0th node at the start
		MemoryNode* memoryNode = (MemoryNode*)m_AllocMemoryStart;
		memoryNode->BlockSize = bytes;
		memoryNode->NextNode = nullptr;

		m_MemoryInitialized = true;

		return m_AllocatedMemory;
	}

	void MemoryManager::Shutdown()
	{
		ASSERT(m_MemoryInitialized);

		PlatformFreeMemory(m_AllocatedMemory);
	}

	void* MemoryManager::PartitionMemory(u32 bytes, u32 count)
	{
		ASSERT(m_MemoryInitialized);

		MemoryNode* currentNode = (MemoryNode*)m_AllocMemoryStart;
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
					smallestValidNode = currentNode;
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
				ASSERT(smallestValidNode != m_AllocMemoryStart);

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
		return (void*)nullptr;
	}

	u32 MemoryManager::GetByteSize(void* location)
	{
		ASSERT(location >= m_AllocMemoryStart);
		ASSERT(location < m_AllocMemoryEnd);

		// Back newLocation up to where we put the header
		PartitionHeader* header = (PartitionHeader*)((u8*)location - sizeof(PartitionHeader));
		return header->Bytes - sizeof(PartitionHeader);
	}

	u32 MemoryManager::GetTotalPartitionedMemory()
	{
		ASSERT(m_MemoryInitialized);

		u32 freeBytes = GetTotalFreeMemory();
		u32 partitionedBytes = (u32)m_AllocMemoryEnd - (u32)m_AllocMemoryStart - freeBytes;

		return partitionedBytes;
	}

	u32 MemoryManager::GetTotalFreeMemory()
	{
		ASSERT(m_MemoryInitialized);

		MemoryNode* currentNode = (MemoryNode*)m_AllocMemoryStart;
		u32 freeBytes = currentNode->BlockSize;

		while (currentNode->NextNode)
		{
			currentNode = currentNode->NextNode;
			freeBytes += currentNode->BlockSize;
		}

		return freeBytes;
	}

	void MemoryManager::DrawMemory()
	{
		ASSERT(m_MemoryInitialized);

		LOG_INFO("%d bytes available, %d bytes used. There are %d nodes in memory.",
			GetTotalFreeMemory(), GetTotalPartitionedMemory(), CountNodes());
	}

	void MemoryManager::RemoveNode(MemoryNode* removedNode)
	{
		MemoryNode* currentNode = (MemoryNode*)m_AllocMemoryStart;

		while (currentNode->NextNode != nullptr)
		{
			if (currentNode->NextNode == removedNode)
				currentNode->NextNode = removedNode->NextNode;
			else
				currentNode = currentNode->NextNode;
		}
	}

	void MemoryManager::AddNode(void* location)
	{
		// Back newLocation up to where we put the header
		void* newLocation = (u8*)location - sizeof(PartitionHeader);
		u32 size = ((PartitionHeader*)newLocation)->Bytes;

		// Create a new memory node at the given location
		MemoryNode* newNode = (MemoryNode*)newLocation;
		newNode->BlockSize = size;

		MemoryNode* previousNode = (MemoryNode*)m_AllocMemoryStart;
		MemoryNode* currentNode = (MemoryNode*)m_AllocMemoryStart;
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

	u32 MemoryManager::CountNodes()
	{
		MemoryNode* currentNode = (MemoryNode*)m_AllocMemoryStart;
		u32 nodeCount = 0;

		while (currentNode)
		{
			nodeCount++;
			currentNode = currentNode->NextNode;
		}

		return nodeCount;
	}
}