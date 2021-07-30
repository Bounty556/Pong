#include "ResourceManager.h"

namespace Soul
{
	ResourceMap* ResourceManager::m_ResourceMap;

	bool ResourceManager::Initialize()
	{
		m_ResourceMap = NEW(ResourceMap);

		return true;
	}

	void ResourceManager::Shutdown()
	{
		DELETE(m_ResourceMap);
	}

	void ResourceManager::UnloadResource(const char* resourceName)
	{
		m_ResourceMap->RemovePair(resourceName);
	}

	void ResourceManager::ClearResources()
	{
		m_ResourceMap->Clear();
	}
}