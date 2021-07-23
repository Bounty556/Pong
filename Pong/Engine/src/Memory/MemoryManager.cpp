#include "MemoryManager.h"

#include <Core/Logger.h>
#include <Platform/Platform.h>

namespace Soul
{
	u8* MemoryManager::m_AllocatedMemory;
	void* MemoryManager::m_AllocMemoryStart;
	void* MemoryManager::m_AllocMemoryEnd;
	MemoryManager::MemoryBlock* MemoryManager::m_LastAllocBlock;
	bool MemoryManager::m_IsInitialized = false;

	bool MemoryManager::Initialize(u32 bytes)
	{
		ASSERT(!m_IsInitialized);

		m_AllocatedMemory = (u8*)PlatformAllocateMemory(bytes);
		m_AllocMemoryStart = m_AllocatedMemory;
		m_AllocMemoryEnd = m_AllocatedMemory + bytes;

		PlatformSetMemory(m_AllocMemoryStart, 0, bytes);
		
		m_IsInitialized = true;

		MemoryBlock* firstBlock = (MemoryBlock*)m_AllocMemoryStart;
		firstBlock->blockSize = bytes;

		m_LastAllocBlock = firstBlock;

		return true;
	}

	void MemoryManager::Shutdown()
	{
		ASSERT(m_IsInitialized);

		PlatformFreeMemory(m_AllocatedMemory);
		m_IsInitialized = false;
	}

	void* MemoryManager::Partition(u32 bytes, u32 count, bool isArray)
	{
		ASSERT(m_IsInitialized);

		MemoryBlock* block = FindFreeBlockOfSize(bytes * count + sizeof(MemoryBlock));
		void* actualMemory = ((u8*)block) + sizeof(MemoryBlock);

		ConfigureMemoryBlocks(block, bytes * count + sizeof(MemoryBlock));

		block->isArray = isArray;
		block->isAllocated = true;
		return actualMemory;
	}

	u32 MemoryManager::GetTotalPartitionedMemory()
	{
		MemoryBlock* currentBlock = (MemoryBlock*)m_AllocMemoryStart;
		u32 totalSize = 0;

		if (currentBlock->isAllocated)
			totalSize += currentBlock->blockSize;

		while (currentBlock->nextBlock)
		{
			currentBlock = currentBlock->nextBlock;

			if (currentBlock->isAllocated)
				totalSize += currentBlock->blockSize;
		}

		return totalSize;
	}

	u32 MemoryManager::GetTotalFreeMemory()
	{
		MemoryBlock* currentBlock = (MemoryBlock*)m_AllocMemoryStart;
		u32 totalSize = 0;

		if (!currentBlock->isAllocated)
			totalSize += currentBlock->blockSize;

		while (currentBlock->nextBlock)
		{
			currentBlock = currentBlock->nextBlock;

			if (!currentBlock->isAllocated)
				totalSize += currentBlock->blockSize;
		}

		return totalSize;
	}

	MemoryManager::MemoryBlock* MemoryManager::FindFreeBlockOfSize(u32 bytes)
	{
		MemoryBlock* currentBlock = m_LastAllocBlock;

		while ((currentBlock->isAllocated || currentBlock->blockSize < bytes) && currentBlock->nextBlock)
			currentBlock = currentBlock->nextBlock;

		if (!currentBlock->isAllocated && currentBlock->blockSize >= bytes)
			return currentBlock;
		else
		{
			LOG_FATAL("Couldn't find free MemoryBlock of requested size.");
			return nullptr;
		}
	}

	void MemoryManager::ConfigureMemoryBlocks(MemoryBlock* location, u32 bytes)
	{
		// Check to see if we can make a new MemoryBlock right after this one
		u8* nextLocation = (u8*)location + bytes;

		// If we have room to make a new block
		if (location->nextBlock)
		{
			if ((u8*)location->nextBlock - nextLocation > sizeof(MemoryBlock))
			{
				u32 oldSize = location->blockSize;
				location->blockSize = bytes;
				MemoryBlock* newBlock = (MemoryBlock*)nextLocation;
				newBlock->nextBlock = location->nextBlock;
				newBlock->prevBlock = location;
				location->nextBlock->prevBlock = newBlock;
				location->nextBlock = newBlock;
				newBlock->isAllocated = false;
				newBlock->blockSize = oldSize - location->blockSize;
				m_LastAllocBlock = newBlock;
			}
			else // We don't have enough room for a new MemoryBlock
				location->blockSize = bytes + ((u8*)location->nextBlock - nextLocation);
		}
		else if ((u8*)m_AllocMemoryEnd - nextLocation > sizeof(MemoryBlock))
		{
			// Check to see if we have room to add a new MemoryBlock
			u32 oldSize = location->blockSize;
			location->blockSize = bytes;
			MemoryBlock* newBlock = (MemoryBlock*)nextLocation;
			newBlock->nextBlock = nullptr;
			newBlock->prevBlock = location;
			location->nextBlock = newBlock;
			newBlock->isAllocated = false;
			newBlock->blockSize = oldSize - location->blockSize;
			m_LastAllocBlock = newBlock;
		}
		else
			LOG_FATAL("Couldn't find suitable memory for new MemoryBlock.");
	}

	void MemoryManager::FreeMemoryBlock(MemoryBlock* location)
	{
		// Special case if we're deleting the very first thing in memory
		if (location == (MemoryBlock*)m_AllocMemoryStart)
		{
			location->isAllocated = false;
			location->isArray = false;
			PlatformSetMemory(location + 1, 0, location->blockSize - sizeof(MemoryBlock));

			m_LastAllocBlock = location;
			CombineFreeBlocks(location);
		}
		else
		{
			MemoryBlock* prevBlock = location->prevBlock;

			location->isAllocated = false;

			if (prevBlock->isAllocated)
			{
				location->isArray = false;
				PlatformSetMemory(location + 1, 0, location->blockSize - sizeof(MemoryBlock));

				m_LastAllocBlock = location;
				CombineFreeBlocks(location);
			}
			else
				CombineFreeBlocks(prevBlock);
		}
	}

	void MemoryManager::CombineFreeBlocks(MemoryBlock* block)
	{
		while (block->nextBlock && !block->nextBlock->isAllocated)
		{
			// Combine this block with the next block
			MemoryBlock* newNext = block->nextBlock->nextBlock;
			block->blockSize += block->nextBlock->blockSize;
			PlatformSetMemory(block->nextBlock, 0, block->nextBlock->blockSize);
			block->nextBlock = newNext;

			if (newNext)
				newNext->prevBlock = block;

			m_LastAllocBlock = block;
		}
	}
}