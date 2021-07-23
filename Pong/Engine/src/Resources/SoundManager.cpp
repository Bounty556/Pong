#include "SoundManager.h"

namespace Soul
{
	SoundManager::SoundManager() :
		m_SoundMap()
	{
	}

	SoundManager::SoundManager(SoundManager&& other) noexcept :
		m_SoundMap(std::move(other.m_SoundMap))
	{
	}

	SoundManager::~SoundManager()
	{
		Vector<sf::SoundBuffer**> buffers = m_SoundMap.GetValues();
		for (u32 i = 0; i < buffers.Count(); ++i)
			DELETE(*(buffers[i]));
	}

	SoundManager& SoundManager::operator=(SoundManager&& other) noexcept
	{
		m_SoundMap = std::move(other.m_SoundMap);
		
		return *this;
	}

	const sf::SoundBuffer* SoundManager::RequestSound(const char* soundName)
	{
		// Check to see if the sound is already allocated.
		sf::SoundBuffer** result = m_SoundMap.GetValue(soundName);

		if (result)
			return *result;
		else
		{
			sf::SoundBuffer* soundBuffer = NEW(sf::SoundBuffer);
			// If not, allocate a new one and return
			if (soundBuffer->loadFromFile(soundName))
			{
				m_SoundMap.AddPair(soundName, soundBuffer);
				return soundBuffer;
			}
			else
				DELETE(soundBuffer);
		}

		return nullptr;
	}

	void SoundManager::ClearAllSounds()
	{
		Vector<sf::SoundBuffer**> buffers = m_SoundMap.GetValues();
		for (u32 i = 0; i < buffers.Count(); ++i)
			DELETE(*(buffers[i]));

		m_SoundMap.Clear();
	}

	u32 SoundManager::Count() const
	{
		return m_SoundMap.Count();
	}
}