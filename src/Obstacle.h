#pragma once
#include "StaticPhysicalEntity.h"
#include "Engine.h"

/*! \brief A solid Peice of Map Geometry.
 * \ingroup Game
 */
class Obstacle : public GameEngine::StaticPhysicalEntity{

	private:
		
		static irr::scene::IAnimatedMesh* _mesh;
		static irr::video::ITexture* _texture;
	
	public:

		//! Constructor.
		Obstacle (const irr::core::vector3df& position, const irr::core::vector3df size);

		//! Destructor.
		~Obstacle();

		void update(float delta){};

		void intitalise(){};

		bool loadContent();
};