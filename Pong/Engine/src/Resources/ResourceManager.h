#pragma once

#include <Defines.h>
#include <Memory/UniquePointer.h>
#include <Structures/Map.h>
#include <Resources/IResource.h>

#define ResourceMap Map<Soul::String, Soul::UniquePointer<Soul::IResource>>

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
			m_ResourceMap->AddPair(resourceName, NEW(T, resourcePath));
	}

	template <class T>
	T* ResourceManager::GetResource(const char* resourceName)
	{
		Soul::UniquePointer<IResource>* found = m_ResourceMap->GetValue(resourceName);
		if (found)
			return (T*)(*found)->GetResource();
		else
			return nullptr;
	}
}