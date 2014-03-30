#pragma once
#include "StaticPhysicalEntity.h"

/*! \brief A solid Peice of Map Geometry.
 * \ingroup Game
 */

class Obstacle : public GameEngine::StaticPhysicalEntity{

	private:
		
		static irr::scene::IMesh* _mesh;
		static irr::video::ITexture* _texture;
	
	public:

		//! Constructor.
		Obstacle (GameEngine::Scene* parentScene,const irr::core::vector3df& position, const irr::core::vector3df size);

		//! Destructor.
		~Obstacle();

		void update(float delta){};

		void intitalise(){};

		bool loadContent();
};
