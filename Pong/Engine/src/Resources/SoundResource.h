#pragma once

#include <Resources/IResource.h>
#include <Memory/UniquePointer.h>

#include <SFML/Audio/SoundBuffer.hpp>

namespace Soul
{
	class SOULAPI SoundResource : public IResource
	{
	public:
		SoundResource(const char* filePath);

		SoundResource(const SoundResource& other) = delete;
		SoundResource(SoundResource&& other) noexcept;

		SoundResource& operator=(const SoundResource& other) = delete;
		SoundResource& operator=(SoundResource&& other) noexcept;

		virtual void* GetResource() override;

	private:
		UniquePointer<sf::SoundBuffer> m_Sound;
	};
}