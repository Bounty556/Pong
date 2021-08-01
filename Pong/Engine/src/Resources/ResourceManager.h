#pragma once

#include <Defines.h>
#include <Structures/Map.h>
#include <Resources/IResource.h>

#define ResourceMap Map<String, IResource>

namespace Soul
{
	class SOULAPI ResourceManager
	{
	public:
		ResourceManager() = delete;

		static bool Initialize();
		static void Shutdown();

		template <class T>
		static void LoadResource(const char* resourcePath, const char* resourceName);

		template <class T>
		static T* GetResource(const char* resourceName);

		static void UnloadResource(const char* resourceName);

		static void ClearResources();

	private:
		static ResourceMap* m_ResourceMap;
	};

	template <class T>
	void ResourceManager::LoadResource(const char* resourcePath, const char* resourceName)
	{
		if (!m_ResourceMap->GetValue(resourceName))
		{
			T resource(resourcePath);
			m_ResourceMap->AddPair(resourceName, std::move(resource));
		}
	}

	template <class T>
	T* ResourceManager::GetResource(const char* resourceName)
	{
		return (T*)m_ResourceMap->GetValue(resourceName);
	}
}