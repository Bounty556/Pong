#include "SoundResource.h"

namespace Soul
{
	SoundResource::SoundResource(const char* filePath) :
		m_Sound(NEW(sf::SoundBuffer))
	{
		if (!m_Sound->loadFromFile(filePath))
		{
			LOG_ERROR("Failed to load sound from path %s", filePath);
			m_Sound = nullptr;
		}
	}

	SoundResource::SoundResource(SoundResource&& other) noexcept :
		m_Sound(std::move(other.m_Sound))
	{
	}

	SoundResource& SoundResource::operator=(SoundResource&& other) noexcept
	{
		m_Sound = std::move(other.m_Sound);

		return *this;
	}

	void* SoundResource::GetResource()
	{
		return m_Sound.Raw();
	}
}