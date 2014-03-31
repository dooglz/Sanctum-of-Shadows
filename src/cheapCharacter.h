#pragma once
#include <irrlicht.h>
#include "Engine.h"
#include "Entity.h"

/*! \brief A character that has no bullet collision, movement controlled by irrlicht
 *  \ingroup Game
 */

class cheapCharacter: public GameEngine::Entity{
	protected:
		//@{
		bool walkforward;
		bool walkback;
		bool walkleft;
		bool walkright;
		//@}

		//@{
		irr::core::vector3df _forwardDir;
		irr::core::vector3df _upDir;
		irr::core::vector3df _strafeDir;
		//@}

		//! Characters have health, this base class does not use it for anything.
		float _health;

		//! Velocity used to scale forward and backwards movement.
		float _walkVelocity;

		//! Used to scale speed of rotating on the spot.
		float _rotateSpeed;

		//! Current bullet trasform of the character
		irr::core::matrix4  _xform;

		//! current posiiton in Irrlicht space, updated by Walk().
		irr::core::vector3df _position;

		//! Move based on the walk flags.
		void walk(float delta);

	public:
		//TODO tidy all this
		//! Constructor, implemeted only to pass name and ID to Entity constructor.
		cheapCharacter(GameEngine::Scene* parentScene, irr::scene::ISceneNode* node,const std::string& name);

		//! Destructor.
		~cheapCharacter();

		//! Creates the controller and adds a blank scene node.
		void intitalise(irr::core::vector3df position, irr::core::vector3df size);

		//! Recalculate position transforms and direction vectors, call this before Walk.
		void update(float delta);

		//! Creates the controller and adds a blank scene node.
		void intitalise(){};

		//! Returns _health.
		float getHealth() { return _health; }

		//! Sets _health.
		void setHealth(float value) {  _health = value; }
};