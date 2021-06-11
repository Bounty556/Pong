#include "Scene.h"

namespace Soul
{
	Scene::Scene(bool updatePass, bool drawPass) :
		m_UpdatePass(updatePass),
		m_DrawPass(drawPass)
	{
	}

	Scene::~Scene()
	{

	}

	void Scene::ResetSceneData(void* data)
	{
	}

	bool Scene::UpdatePass() const
	{
		return m_UpdatePass;
	}

	bool Scene::DrawPass() const
	{
		return m_DrawPass;
	}
}