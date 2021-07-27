#pragma once

#include <Defines.h>

namespace Soul
{
	class SOULAPI ReferenceCounter
	{
	public:
		ReferenceCounter();

		void AddReference();

		u32 RemoveReference();

	private:
		u32 m_Counter;
	};
}