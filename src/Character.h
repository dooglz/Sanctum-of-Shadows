#pragma once
#include <irrlicht.h>
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "Engine.h"
#include "Entity.h"

/*! \brief A character manages an entity that implemets the bullet KinematicCharacterController and a irrlicht render node
 *  \ingroup Game
 */

class Character: public GameEngine::Entity{
	protected:
		//@{
		bool walkforward;
		bool walkback;
		bool walkleft;
		bool walkright;
		//@}

		//@{
		btVector3 _forwardDir;
		btVector3 _upDir;
		btVector3 _strafeDir;
		//@}

		//! Characters have health, this base class does not use it for anything.
		float _health;

		//! Velocity used to scale forward and backwards movement.
		btScalar _walkVelocity;

		//! Used to scale speed of rotating on the spot.
		float _rotateSpeed;

		//! Current bullet trasform of the character
		btTransform _xform;

		//! current posiiton in Irrlicht space, updated by Walk().
		irr::core::vector3df _position;

		//! This ghostobject is used for detecting colliisons.
		btPairCachingGhostObject* _ghostObject;

		//! The btKinematicCharacterController* in use by the character.
		btKinematicCharacterController* _characterC;

		//! Create a new btKinematicCharacterController*.
		btKinematicCharacterController*  addCharacter(btScalar stepHeight,btVector3* characterPosition, btScalar characterHeight, btScalar characterWidth);

		//! Move based on the walk flags.
		void walk(float delta);

	public:
		//TODO tidy all this
		//! Constructor, implemeted only to pass name and ID to Entity constructor.
		Character(GameEngine::Scene* parentScene, irr::scene::ISceneNode* node,const std::string& name);

		//! Destructor.
		~Character();

		//! Creates the controller and adds a blank scene node.
		void intitalise(irr::core::vector3df position, irr::core::vector3df size);

		//! Return the btKinematicCharacterController* in use.
		btKinematicCharacterController* getController() { return _characterC; }

		//! Recalculate position transforms and direction vectors, call this before Walk.
		void update(float delta);

		//! Creates the controller and adds a blank scene node.
		void intitalise(){};

		//! Returns _health.
		float getHealth() { return _health; }

		//! Sets _health.
		void setHealth(float value) {  _health = value; }
};