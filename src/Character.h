#pragma once
#include <irrlicht.h>
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

		//! Characters have health, this base class does not use it for anything.
		float _health;

		//! Velocity used to scale forward and backwards movement.
		float _walkSpeed;

		//! Used to scale speed of rotating on the spot.
		float _rotateSpeed;

		//! current posiiton in Irrlicht space, updated by Walk().
		irr::core::vector3df _position;

		//! Move based on the walk flags.
		virtual void walk(float delta) = 0;

	public:
		//! Constructor, implemeted only to pass name and ID to Entity constructor.
		Character(GameEngine::Scene* parentScene, const std::string& name);

		//! Destructor.
		~Character();

		//! Recalculate position transforms and direction vectors, call this before Walk.
		virtual void update(float delta) = 0;

		virtual void intitalise() = 0;

		//! Returns _health.
		float getHealth() { return _health; }

		//! Sets _health.
		void setHealth(float value) {  _health = value; }
};