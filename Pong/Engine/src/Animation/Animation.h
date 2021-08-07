#pragma once

#include <Defines.h>

#include <Structures/Queue.h>
#include <Animation/AnimationFrame.h>

namespace Soul
{
	/*
	Usage example:

	animation.StartFrame()
			.Lerp(1000, NEW(std::function<void(f32)>, [&](f32 val) { text->SetFontSize(val); }), 30.0f, 5.0f)
		.Then()
			.Call(NEW(std::function<void()>, [&]() { text->SetFontSize(30); }))
			.Call(NEW(std::function<void()>, [&]() { text->SetText("2"); }))
			.Lerp(1000, NEW(std::function<void(f32)>, [&](f32 val) { text->SetFontSize(val); }), 30.0f, 5.0f)
		.Then()
			.Call(NEW(std::function<void()>, [&]() { text->SetFontSize(30); }))
			.Call(NEW(std::function<void()>, [&]() { text->SetText("1"); }))
			.Lerp(1000, NEW(std::function<void(f32)>, [&](f32 val) { text->SetFontSize(val); }), 30.0f, 5.0f)
		.Then()
			.Call(NEW(std::function<void()>, [&]() { text->SetText(""); }))
			.Call(NEW(std::function<void()>, [&]() { Soul::MessageBus::QueueMessage("StartGame"); }));

	Then in the update function:
	
	animation.Update(dt);
	*/
	class SOULAPI Animation
	{
	public:
		Animation();

		Animation(const Animation& other) = delete;
		Animation(Animation&& other) noexcept;

		Animation& operator=(const Animation& other) = delete;
		Animation& operator=(Animation&& other) noexcept;

		Animation& StartFrame();
		Animation& Then();
		
		Animation& Lerp(f32 ms, std::function<void(f32)>* func, f32 init, f32 end);
		Animation& Call(std::function<void()>* func);
		Animation& Wait(f32 ms);

		u32 GetFrameCount() const;

		void Update(f32 dt);

	private:
		Queue<AnimationFrame> m_AnimationFrames;
		bool m_IsAnimating;
	};
}