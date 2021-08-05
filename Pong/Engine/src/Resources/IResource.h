#pragma once

#include <Defines.h>

namespace Soul
{
	class SOULAPI IResource
	{
	public:
		virtual void* GetResource() = 0;

		virtual ~IResource();
	};
}