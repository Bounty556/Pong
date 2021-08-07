#pragma once

#include <Defines.h>
#include <Structures/Vector.h>

#include <functional>

namespace Soul
{
	class AnimationFrame
	{
	public:
		enum StepType
		{
			Call,
			Lerp,
			Wait
		};

	private:
		struct Step
		{
			StepType stepType;
			f32 ms;
			f32 startMs;
			void* functionCall;
			f32 param1;
			f32 param2;
		};

	public:
		AnimationFrame();

		AnimationFrame(const AnimationFrame& other) = delete;
		AnimationFrame(AnimationFrame&& other) noexcept;

		~AnimationFrame();

		AnimationFrame& operator=(const AnimationFrame& other) = delete;
		AnimationFrame& operator=(AnimationFrame&& other) noexcept;

		void AddLerp(f32 ms, std::function<void(f32)>* func, f32 init, f32 end);
		void AddCall(std::function<void()>* func);
		void AddWait(f32 ms);

		void StartFrame();
		void Update(f32 dt);

		bool IsDone() const;

	private:
		Vector<Step> m_Steps;
	};
}