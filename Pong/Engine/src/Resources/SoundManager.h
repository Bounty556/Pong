#pragma once

#include <Defines.h>
#include <Core/String.h>
#include <Structures/Map.h>

#include <SFML/Audio/SoundBuffer.hpp>

#define SoundMap Map<Soul::String, sf::SoundBuffer*>

namespace Soul
{
	/*
	A resource manager class that takes care of loading and unloading Sounds as they are needed.

	Sounds can be requested via RequestSound(...) which will try to return an already-loaded
	sound file if it exists. If it does not exist, the provided sound file will attempt to
	be loaded into memory.
	*/
	class SOULAPI SoundManager
	{
	public:
		SoundManager();

		SoundManager(const SoundManager&) = delete;
		SoundManager(SoundManager&&) noexcept;

		~SoundManager();

		SoundManager& operator=(const SoundManager&) = delete;
		SoundManager& operator=(SoundManager&& other) noexcept;

		const sf::SoundBuffer* RequestSound(const char* soundName);

		void ClearAllSounds();

		u32 Count() const;

	private:
		SoundMap m_SoundMap;
	};
}