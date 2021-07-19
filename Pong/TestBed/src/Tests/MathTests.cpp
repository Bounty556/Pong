#include "MathTests.h"

#include <Core/Logger.h>
#include <Math/Constants.h>
#include <Math/Functions.h>
#include <Math/Random.h>
#include <Math/Vectors.h>
#include <Memory/MemoryManager.h>

#include "../TestMacros.h"

#include <utility>

#include <SFML/System/Vector2.hpp>

void ClampTest()
{
	f32 testFloat = 1269.4578f;
	testFloat = Soul::Math::Clamp(testFloat, 1280.0f, 1281.0f);

	ASSERT_CLOSE(testFloat, 1280.0f, 0.00001f, "Failed to clamp lower bound.");

	f32 testFloat2 = 1300.547f;
	testFloat2 = Soul::Math::Clamp(testFloat2, 1280.0f, 1281.0f);

	ASSERT_CLOSE(testFloat2, 1281.0f, 0.00001f, "Failed to clamp upper bound.");
}

void PowerTest()
{
	ASSERT_EQUAL(Soul::Math::PowInt(15, 3), 3375, "Failed to compute 15^3.");
	ASSERT_EQUAL(Soul::Math::PowInt(-12, 5), -248832, "Failed to compute -12^5.");
	ASSERT_EQUAL(Soul::Math::PowInt(-12, 4), 20736, "Failed to compute -12^4.");
	ASSERT_CLOSE(Soul::Math::PowFloat(6.343f, 3), 255.202035f, 0.0001f, "Failed to compute 6.343^3.");
	ASSERT_CLOSE(Soul::Math::PowFloat(12.589f, -3), 0.00050121758f, 0.00001f, "Failed to compute 12.589^-3.");
	ASSERT_CLOSE(Soul::Math::PowFloat(-4.972f, 4), 611.117161575f, 0.0001f, "Failed to compute -4.972^4.");
	ASSERT_CLOSE(Soul::Math::PowFloat(-7.114f, 3), -360.032397544f, 0.0001f, "Failed to compute -7.114f^3.");
	ASSERT_CLOSE(Soul::Math::PowFloat(-9.415f, -2), 0.01128130526f, 0.00001f, "Failed to compute -9.415^-2.");
	ASSERT_CLOSE(Soul::Math::PowFloat(-4.777f, -3), -0.00917348333f, 0.00001f, "Failed to compute -4.777^-3.");
}

void PrimeTest()
{
	u32 prime = 7;
	prime = Soul::Math::FindNextPrime(prime + 1);
	prime = Soul::Math::FindNextPrime(prime + 1);
	prime = Soul::Math::FindNextPrime(prime + 1);

	ASSERT_EQUAL(prime, 17, "Failed to find next primes.");

	ASSERT_TRUE(Soul::Math::IsPrime(28663), "Failed to identify prime 28663.");
	ASSERT_FALSE(Soul::Math::IsPrime(29103), "Incorrectly identified 29103 as prime.");

	ASSERT_TRUE(Soul::Math::IsPrime(129733), "Failed to identify prime 129733.");
	ASSERT_FALSE(Soul::Math::IsPrime(129717), "Incorrectly identified 129717 as prime.");

	ASSERT_TRUE(Soul::Math::IsPrime(253103), "Failed to identify prime 253103.");
	ASSERT_FALSE(Soul::Math::IsPrime(253107), "Incorrectly identified 253107 as prime.");
}

void AbsTest()
{
	ASSERT_CLOSE(Soul::Math::Abs(-194.123f), 194.123f, 0.001f, "Failed to find absolute value of -194.123f.");
	ASSERT_CLOSE(Soul::Math::Abs(5972.355f), 5972.355f, 0.001f, "Failed to find absolute value of 5972.355f.");
}

void RoundTest()
{
	ASSERT_EQUAL(Soul::Math::Round(-15.446f), -15, "Failed to round -15.446f.");
	ASSERT_EQUAL(Soul::Math::Round(-17.5f), -18, "Failed to round -17.5f.");
	ASSERT_EQUAL(Soul::Math::Round(-21.61f), -22, "Failed to round -21.61f.");
	ASSERT_EQUAL(Soul::Math::Round(27.772f), 28, "Failed to round 27.772f.");
	ASSERT_EQUAL(Soul::Math::Round(35.5f), 36, "Failed to round 35.5f.");
	ASSERT_EQUAL(Soul::Math::Round(41.12f), 41, "Failed to round 41.12f.");
}

void SqrtTest()
{
	ASSERT_CLOSE(Soul::Math::Sqrt(16.0f), 4.0f, 0.0001f, "Failed to find sqrt of 16.0f");
	ASSERT_CLOSE(Soul::Math::Sqrt(270.0f), 16.4316767252f, 0.0001f, "Failed to find sqrt of 270.0f");
	ASSERT_CLOSE(Soul::Math::Sqrt(978.352f), 31.2786198953f, 0.0001f, "Failed to find sqrt of 978.352f");
}

void MinMaxTest()
{
	ASSERT_EQUAL(Soul::Math::Max(5, 10), 10, "Failed to find max of 5 and 10.");
	ASSERT_EQUAL(Soul::Math::Min(5, 10), 5, "Failed to find min of 5 and 10.");
	ASSERT_EQUAL(Soul::Math::Max(674.385f, 947.238f), 947.238f, "Failed to find max of 674.385f and 947.238f.");
	ASSERT_EQUAL(Soul::Math::Min(7.287f, 284.678f), 7.287f, "Failed to find min of 7.287f and 284.678f.");
}

void ConvertRadDegTest()
{
	ASSERT_CLOSE(Soul::Math::ToDegrees(6.8f), 389.611f, 0.001f, "Failed to convert 6.8f radians to degrees.");
	ASSERT_CLOSE(Soul::Math::ToDegrees(-1.87f), -107.1431f, 0.001f, "Failed to convert -1.87f radians to degrees.");
	ASSERT_CLOSE(Soul::Math::ToRadians(389.611f), 6.8f, 0.001f, "Failed to convert 389.611f degrees to radians.");
	ASSERT_CLOSE(Soul::Math::ToRadians(-107.1431f), -1.87, 0.001f, "Failed to convert -107.1431f degrees to radians.");
}

void CosSinTest()
{
	ASSERT_CLOSE(Soul::Math::Cos(PI), -1.0f, 0.0001f, "Failed to find cosine of Pi.");
	ASSERT_CLOSE(Soul::Math::Cos(-1.2 * PI), -0.80901f, 0.001f, "Failed to find cosine of -1.2Pi.");
	ASSERT_CLOSE(Soul::Math::Sin(0.5f * PI), 1.0f, 0.0001f, "Failed to find sine of 1/2Pi");
	ASSERT_CLOSE(Soul::Math::Sin(1.67f * PI), 0.86074f, 0.001f, "Failed to find sine of 1.67Pi.");
}

void ACosASinTest()
{
	ASSERT_CLOSE(Soul::Math::Acos(-1.0f), PI, 0.0001f, "Failed to find inverse cosine of -1.0f.");
	ASSERT_CLOSE(Soul::Math::Acos(-0.80901f), 2.51326222f, 0.001f, "Failed to find inverse cosine of -0.80901f.");
	ASSERT_CLOSE(Soul::Math::Asin(1.0f), 0.5f * PI, 0.0001f, "Failed to find inverse sine of 1.0f.");
	ASSERT_CLOSE(Soul::Math::Asin(0.86074f), 1.03672159f, 0.001f, "Failed to find inverse sine of 0.86074f.");
}

void ATanTest()
{
	ASSERT_CLOSE(Soul::Math::Atan2(4.56f, 2.55f), 1.0609f, 0.001f, "Failed to find four quadrant inverse tangent of (y,x)(4.56f, 1.55f).");
	ASSERT_CLOSE(Soul::Math::Atan2(-1.66f, 8.1f), -0.20213f, 0.001f, "Failed to find four quadrant inverse tangent of (y,x)(4-1.66, 8.1f).");
	ASSERT_CLOSE(Soul::Math::Atan2(-3.61f, -9.62f), -2.78259, 0.001f, "Failed to find four quadrant inverse tangent of (y,x)(-3.61f, -9.62f).");
	ASSERT_CLOSE(Soul::Math::Atan2(5.93f, -6.19f), 2.37764f, 0.001f, "Failed to find four quadrant inverse tangent of (y,x)(5.93f, -6.19f).");
}

void DistanceTest()
{
	ASSERT_CLOSE(Soul::Math::Distance(sf::Vector2f(5.0f, 5.0f), sf::Vector2f(6.0, 6.0f)), 1.44f, 0.001f, "Failed to calculate distance between points (5.0f, 5.0f) and (6.0f, 6.0f).");
}

void MagnitudeTest()
{
	ASSERT_CLOSE(Soul::Math::Magnitude(sf::Vector2f(-1.0f, 1.0f)), 1.44f, 0.001f, "Failed to calculate magnitude of (-1.0f, 1.0f).");
}

void NormalizeTest()
{
	sf::Vector2f normalized = Soul::Math::Normalize(sf::Vector2f(15.0f, 12.0f));
	ASSERT_CLOSE(normalized.x, 0.780868f, 0.001f, "Failed to normalized (15.0f, 12.0f).");
	ASSERT_CLOSE(normalized.y, 0.624695f, 0.001f, "Failed to normalized (15.0f, 12.0f).");
}

void NormalTest()
{
	sf::Vector2f normal = Soul::Math::Normal(sf::Vector2f(15.0f, 12.0f));
	ASSERT_CLOSE(normal.x, -12.0f, 0.001f, "Failed to find normal vector for (15.0f, 12.0f).");
	ASSERT_CLOSE(normal.y, 15.0f, 0.001f, "Failed to find normal vector for (15.0f, 12.0f).");
}

void AngleToVectorTest()
{
	sf::Vector2f result = Soul::Math::AngleToVector(45.0f);
	sf::Vector2f result1 = Soul::Math::AngleToVector(135.0f);
	sf::Vector2f result2 = Soul::Math::AngleToVector(225.0f);
	sf::Vector2f result3 = Soul::Math::AngleToVector(315.0f);

	ASSERT_CLOSE(result.x, 0.70710f, 0.001f, "Failed to calculate vector from angle 45 degrees.");
	ASSERT_CLOSE(result.y, 0.70710f, 0.001f, "Failed to calculate vector from angle 45 degrees.");

	ASSERT_CLOSE(result1.x, -0.70710f, 0.001f, "Failed to calculate vector from angle 135 degrees.");
	ASSERT_CLOSE(result1.y, 0.70710f, 0.001f, "Failed to calculate vector from angle 135 degrees.");

	ASSERT_CLOSE(result2.x, -0.70710f, 0.001f, "Failed to calculate vector from angle 225 degrees.");
	ASSERT_CLOSE(result2.y, -0.70710f, 0.001f, "Failed to calculate vector from angle 225 degrees.");

	ASSERT_CLOSE(result3.x, 0.70710f, 0.001f, "Failed to calculate vector from angle 315 degrees.");
	ASSERT_CLOSE(result3.y, -0.70710f, 0.001f, "Failed to calculate vector from angle 315 degrees.");
}

void VectorToAngleTest()
{
	ASSERT_CLOSE(Soul::Math::VectorToAngle(sf::Vector2f(0.70710f, 0.70710f)), 45.0f, 0.001f, "Failed to calculate angle from vector (0.70710f, 0.70710f).");
	ASSERT_CLOSE(Soul::Math::VectorToAngle(sf::Vector2f(-0.70710f, 0.70710f)), 135.0f, 0.001f, "Failed to calculate angle from vector (-0.70710f, 0.70710f).");
	ASSERT_CLOSE(Soul::Math::VectorToAngle(sf::Vector2f(-0.70710f, -0.70710f)), 225.0f, 0.001f, "Failed to calculate angle from vector (-0.70710f, -0.70710f).");
	ASSERT_CLOSE(Soul::Math::VectorToAngle(sf::Vector2f(0.70710f, -0.70710f)), 315.0f, 0.001f, "Failed to calculate angle from vector (0.70710f, -0.70710f).");
}

void Random64Test()
{
	for (u32 i = 0; i < 500; ++i)
		ASSERT_BETWEEN(Soul::Math::Rand(100), 0, 100, "Failed to generate number in correct range.");

	for (u32 i = 0; i < 500; ++i)
		ASSERT_BETWEEN(Soul::Math::Rand(100, 200), 100, 200, "Failed to generate number in correct range.");
}

void Random32Test()
{
	for (u32 i = 0; i < 500; ++i)
		ASSERT_BETWEEN(Soul::Math::Rand32(100), 0, 100, "Failed to generate number in correct range.");

	for (u32 i = 0; i < 500; ++i)
		ASSERT_BETWEEN(Soul::Math::Rand32(100, 200), 100, 200, "Failed to generate number in correct range.");
}

void MathTests::RunAllTests()
{
	RUN_TEST(ClampTest);
	RUN_TEST(PowerTest);
	RUN_TEST(PrimeTest);
	RUN_TEST(AbsTest);
	RUN_TEST(RoundTest);
	RUN_TEST(SqrtTest);
	RUN_TEST(MinMaxTest);
	RUN_TEST(ConvertRadDegTest);
	RUN_TEST(CosSinTest);
	RUN_TEST(ACosASinTest);
	RUN_TEST(ATanTest);
	RUN_TEST(DistanceTest);
	RUN_TEST(MagnitudeTest);
	RUN_TEST(NormalizeTest);
	RUN_TEST(NormalTest);
	RUN_TEST(AngleToVectorTest);
	RUN_TEST(VectorToAngleTest);
	RUN_TEST(Random64Test);
	RUN_TEST(Random32Test);
}