#pragma once

#include <Defines.h>
#include <Core/Logger.h>
#include <Platform/Timer.h>

#define TO_STRING(x) #x
#define STRINGIFY(x) TO_STRING(x)

#define CREATE_TEST_SUITE(x) { \
	LOG_WARN("Running Suite " STRINGIFY(x)); \
	Soul::Timer timer; \
	timer.Start(); \
	RunTestSuite(new x); \
	LOG_WARN("Suite took %dms milliseconds to run", timer.GetElapsedMilliseconds()); \
}

#define RUN_TEST(x) LOG_INFO("Running test " STRINGIFY(x)); \
x();

#define START_MEMORY_CHECK() u32 CURRENT_MEMORY_BYTES_ALLOCATED = Soul::MemoryManager::GetTotalPartitionedMemory(); \
{

#define END_MEMORY_CHECK() } \
if (CURRENT_MEMORY_BYTES_ALLOCATED != Soul::MemoryManager::GetTotalPartitionedMemory()) \
	LOG_ERROR("Memory leak detected in test. Ended with %d bytes of memory allocated, expected %d bytes.", Soul::MemoryManager::GetTotalPartitionedMemory(), CURRENT_MEMORY_BYTES_ALLOCATED);

#define ASSERT_EQUAL(x, y, msg) if ((x) != (y)) \
{ \
	LOG_ERROR("Test failed on line " STRINGIFY(__LINE__) ". " msg); \
	return; \
}

#define ASSERT_NOT_EQUAL(x, y, msg) if ((x) == (y)) \
{ \
	LOG_ERROR("Test failed on line " STRINGIFY(__LINE__) ". " msg); \
	return; \
}

#define ASSERT_TRUE(x, msg) if (!(x)) \
{ \
	LOG_ERROR("Test failed on line " STRINGIFY(__LINE__) ". " msg); \
	return; \
}

#define ASSERT_FALSE(x, msg) if ((x)) \
{ \
	LOG_ERROR("Test failed on line " STRINGIFY(__LINE__) ". " msg); \
	return; \
}

#define ASSERT_CLOSE(x, y, threshold, msg) if ((x) - (y) > threshold) \
{ \
	LOG_ERROR("Test failed on line " STRINGIFY(__LINE__) ". " msg); \
	return ; \
}