#pragma once

namespace Soul
{
	class ReferenceCounter
	{
	public:
		ReferenceCounter();

		void AddReference();

		unsigned int RemoveReference();

	private:
		unsigned int m_Counter;
	};
}