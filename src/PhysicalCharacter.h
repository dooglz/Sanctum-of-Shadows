#pragma once
#include <irrlicht.h>
#include "Character.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "Engine.h"
#include "Entity.h"

/*! \brief A character manages an entity that implemets the bullet KinematicCharacterController and a irrlicht render node
 *  \ingroup Game
 */

class PhysicalCharacter: public Character{
	protected:
		//@{
		btVector3 _forwardDir;
		btVector3 _upDir;
		btVector3 _strafeDir;
		//@}

		//! Current bullet transform of the character
		btTransform _xform;

		//! current position in Irrlicht space, updated by Walk().
		irr::core::vector3df _position;

		//! This ghostobject is used for detecting collisions.
		btPairCachingGhostObject* _ghostObject;

		//! The btKinematicCharacterController* in use by the character.
		btKinematicCharacterController* _characterC;

		//! Create a new btKinematicCharacterController*.
		btKinematicCharacterController*  addbtKinematicCharacterController(btScalar stepHeight,btVector3* characterPosition, btScalar characterHeight, btScalar characterWidth);

		//! Move based on the walk flags.
		void walk(float delta);

	public:
		//TODO tidy all this
		//! Constructor, implemented only to pass name and ID to Entity constructor.
		PhysicalCharacter(GameEngine::Scene* parentScene,const std::string& name);

		//! Destructor.
		~PhysicalCharacter();

		//! Creates the controller and adds a blank scene node.
		void intitalise(irr::core::vector3df position, irr::core::vector3df size);

		//! Return the btKinematicCharacterController* in use.
		btKinematicCharacterController* getController() { return _characterC; }

		//! Recalculate position transforms and direction vectors, call this before Walk.
		void update(float delta);

		//! Creates the controller and adds a blank scene node.
		void intitalise(){};
};