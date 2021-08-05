#pragma once

#include <Resources/IResource.h>
#include <Memory/UniquePointer.h>

#include <SFML/Graphics/Texture.hpp>

namespace Soul
{
	class SOULAPI TextureResource : public IResource
	{
	public:
		TextureResource(const char* filePath);

		TextureResource(const TextureResource& other) = delete;
		TextureResource(TextureResource&& other) noexcept;

		TextureResource& operator=(const TextureResource& other) = delete;
		TextureResource& operator=(TextureResource&& other) noexcept;

		virtual void* GetResource() override;

	private:
		UniquePointer<sf::Texture> m_Texture;
	};
}