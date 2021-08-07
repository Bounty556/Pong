#include "Animation.h"

namespace Soul
{
	Animation::Animation() :
		m_AnimationFrames(),
		m_IsAnimating(false)
	{
	}

	Animation::Animation(Animation&& other) noexcept :
		m_AnimationFrames(std::move(other.m_AnimationFrames)),
		m_IsAnimating(other.m_IsAnimating)
	{
	}

	Animation& Animation::operator=(Animation&& other) noexcept
	{
		m_AnimationFrames = std::move(other.m_AnimationFrames);
		m_IsAnimating = other.m_IsAnimating;

		return *this;
	}

	Animation& Animation::StartFrame()
	{
		m_AnimationFrames.Que(AnimationFrame());
		
		return *this;
	}

	Animation& Animation::Then()
	{
		m_AnimationFrames.Que(AnimationFrame());
		
		return *this;
	}

	Animation& Animation::Lerp(f32 ms, std::function<void(f32)>* func, f32 init, f32 end)
	{
		ASSERT(m_AnimationFrames.Count() > 0);
		
		m_AnimationFrames.PeekEnd().AddLerp(ms, func, init, end);
		
		return *this;
	}

	Animation& Animation::Call(std::function<void()>* func)
	{
		ASSERT(m_AnimationFrames.Count() > 0);
		m_AnimationFrames.PeekEnd().AddCall(func);
		
		return *this;
	}

	Animation& Animation::Wait(f32 ms)
	{
		ASSERT(m_AnimationFrames.Count() > 0);
		m_AnimationFrames.PeekEnd().AddWait(ms);
		
		return *this;
	}

	u32 Animation::GetFrameCount() const
	{
		return m_AnimationFrames.Count();
	}

	void Animation::Update(f32 dt)
	{
		if (!m_IsAnimating && m_AnimationFrames.Count() > 0)
		{
			m_IsAnimating = true;
			m_AnimationFrames.Peek().StartFrame();
		}

		if (m_IsAnimating)
		{
			m_AnimationFrames.Peek().Update(dt);
			if (m_AnimationFrames.Peek().IsDone())
			{
				m_AnimationFrames.Deque();
				m_IsAnimating = false;
			}
		}
	}
}