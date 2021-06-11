#include "TextureManager.h"

namespace Soul
{
	TextureManager::TextureManager() :
		m_TextureMap()
	{
	}

	TextureManager::TextureManager(TextureManager&& other) noexcept :
		m_TextureMap(std::move(other.m_TextureMap))
	{
	}

	TextureManager::~TextureManager()
	{
		ClearAllTextures();
	}

	TextureManager& TextureManager::operator=(TextureManager&& other) noexcept
	{
		m_TextureMap = std::move(other.m_TextureMap);

		return *this;
	}

	const sf::Texture* TextureManager::RequestTexture(const char* textureName)
	{
		// Check to see if the texture is already allocated.
		sf::Texture** result = m_TextureMap.GetValue(textureName);

		if (result)
			return *result;
		else
		{
			sf::Texture* texture = PARTITION(sf::Texture);
			// If not, allocate a new one and return
			if (texture->loadFromFile(textureName))
			{
				m_TextureMap.AddPair(textureName, texture);
				return texture;
			}
			else
				MemoryManager::FreeMemory(texture);
		}

		return nullptr;
	}

	void TextureManager::ClearAllTextures()
	{
		Vector<sf::Texture**> textures = m_TextureMap.GetValues();
		for (u32 i = 0; i < textures.Count(); ++i)
			MemoryManager::FreeMemory(*(textures[i]));

		m_TextureMap.Clear();
	}

	u32 TextureManager::Count() const
	{
		return m_TextureMap.Count();
	}
}