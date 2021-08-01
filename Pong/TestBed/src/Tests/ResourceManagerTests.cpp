#include "ResourceManagerTests.h"

#include <Memory/MemoryManager.h>
#include <Resources/ResourceManager.h>
#include <Resources/TextureResource.h>
#include <Resources/SoundResource.h>

#include "../TestMacros.h"

void TextureResourceTest()
{
	START_MEMORY_CHECK();

	Soul::ResourceManager::LoadResource<Soul::TextureResource>("res/player.png", "Player");

	Soul::TextureResource* resource = Soul::ResourceManager::GetResource<Soul::TextureResource>("Player");

	ASSERT_NOT_EQUAL(resource, nullptr, "Failed to load and retrieve resource.");

	Soul::ResourceManager::UnloadResource("Player");

	Soul::TextureResource* resource2 = Soul::ResourceManager::GetResource<Soul::TextureResource>("Player");

	ASSERT_EQUAL(resource2, nullptr, "Failed to delete resource.");

	END_MEMORY_CHECK();
}

void SoundResourceTest()
{
	START_MEMORY_CHECK();

	Soul::ResourceManager::LoadResource<Soul::SoundResource>("res/sound.ogg", "Sound");

	Soul::SoundResource* resource = Soul::ResourceManager::GetResource<Soul::SoundResource>("Sound");

	ASSERT_NOT_EQUAL(resource, nullptr, "Failed to load and retrieve resource.");

	Soul::ResourceManager::UnloadResource("Sound");

	Soul::SoundResource* resource2 = Soul::ResourceManager::GetResource<Soul::SoundResource>("Sound");

	ASSERT_EQUAL(resource2, nullptr, "Failed to delete resource.");

	END_MEMORY_CHECK();
}
void ResourceManagerTests::RunAllTests()
{
	RUN_TEST(TextureResourceTest);
	RUN_TEST(SoundResourceTest);
}