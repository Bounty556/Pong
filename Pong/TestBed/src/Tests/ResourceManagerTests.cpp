#include "ResourceManagerTests.h"

#include <Memory/MemoryManager.h>
#include <Resources/FontResource.h>
#include <Resources/ResourceManager.h>
#include <Resources/SoundResource.h>
#include <Resources/TextureResource.h>

#include "../TestMacros.h"

void TextureResourceTest()
{
	START_MEMORY_CHECK();

	Soul::ResourceManager::LoadResource<Soul::TextureResource>("res/player.png", "Player");

	/*sf::Texture* resource = Soul::ResourceManager::GetResource<sf::Texture>("Player");
	ASSERT_NOT_EQUAL(resource, nullptr, "Failed to load and retrieve sf::Texture.");*/

	Soul::ResourceManager::UnloadResource("Player");
	/*sf::Texture* resource2 = Soul::ResourceManager::GetResource<sf::Texture>("Player");
	ASSERT_EQUAL(resource2, nullptr, "Failed to delete resource.");*/

	END_MEMORY_CHECK();
}

void SoundResourceTest()
{
	START_MEMORY_CHECK();

	Soul::ResourceManager::LoadResource<Soul::SoundResource>("res/sound.ogg", "Sound");

	sf::SoundBuffer* resource = Soul::ResourceManager::GetResource<sf::SoundBuffer>("Sound");
	ASSERT_NOT_EQUAL(resource, nullptr, "Failed to load and retrieve sf::SoundBuffer.");

	Soul::ResourceManager::UnloadResource("Sound");
	sf::SoundBuffer* resource2 = Soul::ResourceManager::GetResource<sf::SoundBuffer>("Sound");
	ASSERT_EQUAL(resource2, nullptr, "Failed to delete resource.");

	END_MEMORY_CHECK();
}

void FontResourceTest()
{
	START_MEMORY_CHECK();

	Soul::ResourceManager::LoadResource<Soul::FontResource>("res/Fonts/font.otf", "Font");

	sf::Font* resource = Soul::ResourceManager::GetResource<sf::Font>("Font");
	ASSERT_NOT_EQUAL(resource, nullptr, "Failed to load and retrieve sf::Font.");

	Soul::ResourceManager::UnloadResource("Font");
	sf::Font* resource2 = Soul::ResourceManager::GetResource<sf::Font>("Font");
	ASSERT_EQUAL(resource2, nullptr, "Failed to delete resource.");

	END_MEMORY_CHECK();
}

void ResourceManagerTests::RunAllTests()
{
	RUN_TEST(TextureResourceTest);
	RUN_TEST(SoundResourceTest);
	RUN_TEST(FontResourceTest);
}