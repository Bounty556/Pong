#include "TextureResource.h"

namespace Soul
{
	TextureResource::TextureResource(const char* filePath) :
		m_Texture(NEW(sf::Texture))
	{
		if (!m_Texture->loadFromFile(filePath))
		{
			LOG_ERROR("Failed to load texture from path %s", filePath);
			m_Texture = nullptr;
		}
	}

	TextureResource::TextureResource(TextureResource&& other) noexcept :
		m_Texture(std::move(other.m_Texture))
	{
	}

	TextureResource& TextureResource::operator=(TextureResource&& other) noexcept
	{
		m_Texture = std::move(other.m_Texture);

		return *this;
	}

	void* TextureResource::GetResource()
	{
		return m_Texture.Raw();
	}
}