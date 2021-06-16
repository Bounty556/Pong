#pragma once

#include <Defines.h>
#include <Core/Logger.h>

#define TO_STIRNG(x) #x
#define STRINGIFY(x) TO_STRING(x)

#define CREATE_TEST_SUITE(x) LOG_WARN("Running Suite " STRINGIFY(x));

#define RUN_TEST(x) LOG_INFO("Running test " STRINGIFY(x)); \
if (x()) \
	LOG_ERROR("All tests passed!");

#define ASSERT_EQUAL(x, y, msg) if ((x) != (y)) \
{ \
	LOG_ERROR("Test failed on line " STRINGIFY(__LINE__) ". " msg); \
	return false; \
}

#define ASSERT_NOT_EQUAL(x, y, msg) if ((x) == (y)) \
{ \
	LOG_ERROR("Test failed on line " STRINGIFY(__LINE__) ". " msg); \
	return false; \
}

#define ASSERT_TRUE(x, msg) if (!(x)) \
{ \
	LOG_ERROR("Test failed on line " STRINGIFY(__LINE__) ". " msg); \
	return false; \
}

#define ASSERT_FALSE(x, msg) if ((x)) \
{ \
	LOG_ERROR("Test failed on line " STRINGIFY(__LINE__) ". " msg); \
	return false; \
}

#define ASSERT_CLOSE(x, y, threshold, msg) if ((x) - (y) > threshold) \
{ \
	LOG_ERROR("Test failed on line " STRINGIFY(__LINE__) ". " msg); \
	return false; \
}