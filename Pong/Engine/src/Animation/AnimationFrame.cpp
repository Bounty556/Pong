#include "AnimationFrame.h"

#include <Math/Functions.h>

namespace Soul
{
	AnimationFrame::AnimationFrame() :
		m_Steps()
	{
	}

	AnimationFrame::AnimationFrame(AnimationFrame&& other) noexcept :
		m_Steps(std::move(other.m_Steps))
	{
	}

	AnimationFrame::~AnimationFrame()
	{
		for (u32 i = 0; i < m_Steps.Count(); ++i)
			DELETE(m_Steps[i].functionCall);
	}

	AnimationFrame& AnimationFrame::operator=(AnimationFrame&& other) noexcept
	{
		m_Steps = std::move(other.m_Steps);

		return *this;
	}

	void AnimationFrame::AddLerp(f32 ms, std::function<void(f32)>* func, f32 init, f32 end)
	{
		m_Steps.Push({ StepType::Lerp, ms, ms, (void*)func, init, end });
	}

	void AnimationFrame::AddCall(std::function<void()>* func)
	{
		m_Steps.Push({ StepType::Call, 0.0f, 0.0f, (void*)func, 0.0f, 0.0f });
	}

	void AnimationFrame::AddWait(f32 ms)
	{
		m_Steps.Push({ StepType::Wait, ms, ms, nullptr, 0.0f, 0.0f });
	}

	void AnimationFrame::StartFrame()
	{
		for (u32 i = 0; i < m_Steps.Count(); ++i)
			if (m_Steps[i].stepType == StepType::Call)
				(*(std::function<void()>*)m_Steps[i].functionCall)();
	}

	void AnimationFrame::Update(f32 dt)
	{
		for (u32 i = 0; i < m_Steps.Count(); ++i)
		{
			m_Steps[i].ms = Math::Max(0.0f, m_Steps[i].ms - dt);
			if (m_Steps[i].stepType == StepType::Lerp && m_Steps[i].ms > 0.0f)
				(*(std::function<void(f32)>*)m_Steps[i].functionCall)(Math::Lerp(m_Steps[i].param1, m_Steps[i].param2, m_Steps[i].ms / m_Steps[i].startMs));
		}
	}

	bool AnimationFrame::IsDone() const
	{
		for (u32 i = 0; i < m_Steps.Count(); ++i)
			if (m_Steps[i].ms > 0.0f)
				return false;

		return true;
	}
}