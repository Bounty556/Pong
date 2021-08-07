#include "AnimationTests.h"

#include <Defines.h>
#include <Animation/Animation.h>
#include <Memory/MemoryManager.h>

#include "../TestMacros.h"

void AnimationCallTest()
{
	START_MEMORY_CHECK();

	Soul::Animation animation;
	u32 testInt = 0;

	animation.StartFrame().Call(NEW(std::function<void()>, [&]() { testInt = 1; }));

	ASSERT_EQUAL(testInt, 0, "Animation started too early.");
	ASSERT_EQUAL(animation.GetFrameCount(), 1, "Incorrect number of animation frames stored.");

	animation.Update(1000.0f);

	ASSERT_EQUAL(testInt, 1, "Animation failed to execute.");
	ASSERT_EQUAL(animation.GetFrameCount(), 0, "Animation frame failed to clean up.");

	END_MEMORY_CHECK();
}

void ChainedAnimationCallsTest()
{
	START_MEMORY_CHECK();

	Soul::Animation animation;
	u32 testInt = 0;
	u32 testInt2 = 5;

	animation.StartFrame().Call(NEW(std::function<void()>, [&]() { testInt = 1; }))
		.Then().Call(NEW(std::function<void()>, [&]() { testInt2 = 10; }));

	ASSERT_EQUAL(testInt, 0, "Animation started too early.");
	ASSERT_EQUAL(testInt2, 5, "Animation started too early.");
	ASSERT_EQUAL(animation.GetFrameCount(), 2, "Incorrect number of animation frames stored.");

	animation.Update(1000.0f);

	ASSERT_EQUAL(testInt, 1, "Animation failed to execute.");
	ASSERT_EQUAL(testInt2, 5, "Chained animation frame executed too early.");
	ASSERT_EQUAL(animation.GetFrameCount(), 1, "Animation frame failed to clean up.");

	animation.Update(1000.0f);

	ASSERT_EQUAL(testInt2, 10, "Failed to execute chained animation.");
	ASSERT_EQUAL(animation.GetFrameCount(), 0, "Animation frame failed to clean up.");

	END_MEMORY_CHECK();
}

void AnimationWaitTest()
{
	START_MEMORY_CHECK();

	Soul::Animation animation;
	u32 testInt = 0;
	u32 testInt2 = 5;

	animation.StartFrame().Call(NEW(std::function<void()>, [&]() { testInt = 1; })).Wait(2000.0f)
		.Then().Call(NEW(std::function<void()>, [&]() { testInt2 = 10; }));

	ASSERT_EQUAL(testInt, 0, "Animation started too early.");
	ASSERT_EQUAL(testInt2, 5, "Animation started too early.");
	ASSERT_EQUAL(animation.GetFrameCount(), 2, "Incorrect number of animation frames stored.");

	animation.Update(500.0f);

	ASSERT_EQUAL(testInt, 1, "Animation failed to execute.");
	ASSERT_EQUAL(testInt2, 5, "Chained animation frame executed too early.");
	ASSERT_EQUAL(animation.GetFrameCount(), 2, "Animation frame cleaned up too early.");

	animation.Update(500.0f);

	ASSERT_EQUAL(testInt2, 5, "Chained animation frame executed too early.");
	ASSERT_EQUAL(animation.GetFrameCount(), 2, "Animation frame cleaned up too early.");

	animation.Update(1000.0f);

	ASSERT_EQUAL(animation.GetFrameCount(), 1, "Animation failed to cleanup.");

	animation.Update(100.0f);

	ASSERT_EQUAL(testInt2, 10, "Failed to execute chained animation.");
	ASSERT_EQUAL(animation.GetFrameCount(), 0, "Animation frame failed to clean up.");

	END_MEMORY_CHECK();
}

void BasicLerpTest()
{
	START_MEMORY_CHECK();

	Soul::Animation animation;

	f32 testFloat = 0.0f;

	animation.StartFrame().Lerp(1000.0f, NEW(std::function<void(f32)>, [&](f32 val) { testFloat = val; }), 0.0f, 10.0f);

	animation.Update(100.0f);
	ASSERT_CLOSE(testFloat, 1.0f, 0.01f, "Failed to lerp float.");

	animation.Update(300.0f);
	ASSERT_CLOSE(testFloat, 4.0f, 0.01f, "Failed to lerp float.");

	animation.Update(1000.0f);
	ASSERT_CLOSE(testFloat, 10.0f, 0.01f, "Failed to finish lerp animation.");

	END_MEMORY_CHECK();
}

void AnimationTests::RunAllTests()
{
	RUN_TEST(AnimationCallTest);
	RUN_TEST(ChainedAnimationCallsTest);
	RUN_TEST(AnimationWaitTest);
	RUN_TEST(BasicLerpTest);
}
