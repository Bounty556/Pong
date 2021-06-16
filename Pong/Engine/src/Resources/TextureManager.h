#pragma once

#include <Defines.h>
#include <Core/String.h>
#include <Structures/Map.h>

#include <SFML/Graphics/Texture.hpp>

#define TextureMap Map<Soul::String, sf::Texture*>

namespace Soul
{
	/*
	A resource manager class that takes care of loading and unloading textures as they are
	needed.

	Textures can be requested via RequestTexture(...) which will try to return an already-loaded
	texture file if it exists. If it does not exist, the provided texture file will attempt to
	be loaded into memory.
	*/
	class SOULAPI TextureManager
	{
	public:
		TextureManager();

		TextureManager(const TextureManager&) = delete;
		TextureManager(TextureManager&& other) noexcept;
		
		~TextureManager();

		TextureManager& operator=(const TextureManager&) = delete;
		TextureManager& operator=(TextureManager&& other) noexcept;

		const sf::Texture* RequestTexture(const char* textureName, bool isRepeated = false);

		void ClearAllTextures();

		u32 Count() const;

	private:
		TextureMap m_TextureMap;
	};
}