#pragma once
#include "PhysicalEntity.h"

/*! \brief An implemented Physical Entity for testing
 *
 *  \ingroup Game
 */
class Box : public GameEngine::PhysicalEntity{
	private:
		static irr::core::vector3df _velocity;
	public:

		Box (const btVector3& position, const irr::core::vector3df& scale, float mass);
		~Box (){};
		void intitalise();
		bool loadContent();
		void unloadContent(){};
		void update(float delta);
		//
		static irr::core::vector3df getVelocity() { return _velocity; }
		static void setVelocity(const irr::core::vector3df& value){ _velocity = value; }
		//
		void handleMessage(const GameEngine::Message& message);
};