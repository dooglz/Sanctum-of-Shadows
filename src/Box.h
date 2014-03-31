#pragma once
#include "PhysicalEntity.h"

/*! \brief An implemented Physical Entity for testing
 *
 *  \ingroup Game
 */

class Box : public GameEngine::PhysicalEntity{
	public:

		//! Constructor
		Box (GameEngine::Scene* parentScene, const btVector3& position, const irr::core::vector3df& scale, float mass);

		//! Destructor
		~Box (){};

		void intitalise(){};

		bool loadContent();

		void update(float delta);

		void handleMessage(const GameEngine::Message& message);
};
