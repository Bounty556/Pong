#pragma once

#include <Defines.h>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace Soul
{
	/*
	An abstract base scene class. To be used in the SceneManager.
	*/
	class SOULAPI Scene
	{
	public:
		Scene(bool updatePass = true, bool drawPass = true);
		virtual ~Scene();

		/*
		Updating and drawing the scene and the objects within
		*/
		virtual void Update(f32 dt) = 0;
		virtual void Draw(sf::RenderStates states) const = 0;

		/*
		If this scene is reset, we can pass data to it to give it some initial
		information to start the scene off with.
		*/
		virtual void ResetSceneData(void* data);

		/*
		Can scenes below this in the Scene stack be updated or drawn?
		*/
		bool UpdatePass() const;
		bool DrawPass() const;
		
	private:
		/*
		Can scenes below this in the Scene stack be updated or drawn?
		*/
		bool m_UpdatePass;
		bool m_DrawPass;
	};
}