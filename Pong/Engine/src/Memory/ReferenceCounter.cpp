#include "ReferenceCounter.h"

namespace Soul
{
	ReferenceCounter::ReferenceCounter() : 
		m_Counter(0)
	{
	}

	void ReferenceCounter::AddReference()
	{
		++m_Counter;
	}

	u32 ReferenceCounter::RemoveReference()
	{
		return --m_Counter;
	}
}