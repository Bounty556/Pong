#include "MathTests.h"

#include <Core/Logger.h>
#include <Math/Functions.h>
#include <Memory/MemoryManager.h>

#include "../TestMacros.h"

#include <utility>

void ClampTest()
{
	f32 testFloat = 1269.4578f;
	Soul::Math::Clamp(testFloat, 1280.0f, 1281.0f);

	ASSERT_CLOSE(testFloat, 1280.0f, 0.00001f, "Failed to clamp lower bound.");

	f32 testFloat2 = 1300.547f;
	Soul::Math::Clamp(testFloat2, 1280.0f, 1281.0f);

	ASSERT_CLOSE(testFloat2, 1281.0f, 0.00001f, "Failed to clamp upper bound.");
}

void PowerTest()
{
	i32 positiveInt = Soul::Math::PowInt(15, 3);
	ASSERT_EQUAL(positiveInt, 3375, "Failed to compute 15^3.");

	i32 negativeInt = Soul::Math::PowInt(-12, 5);
	ASSERT_EQUAL(negativeInt, -248832, "Failed to compute -12^5.");

	i32 negativePositiveInt = Soul::Math::PowInt(-12, 4);
	ASSERT_EQUAL(negativePositiveInt, 20736, "Failed to compute -12^4.");
}

void MathTests::RunAllTests()
{
	RUN_TEST(ClampTest);
	RUN_TEST(PowerTest);
}