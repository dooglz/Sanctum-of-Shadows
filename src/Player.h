#pragma once
#include <irrlicht.h>
#include "Character.h"

/*! \brief The player.
 * \ingroup Game
 */

class Player:public Character{
	private:
		
		//! The primary camera.
		irr::scene::ICameraSceneNode* _camera;
		
		//! Light scene node, used as the lantern. 
		irr::scene::ILightSceneNode* _Lanternlight;
		
		//! The Maximum radius of the lanterns effects.
		static const float _Lanternmaxradius;
		
		//! Current state of the lantern.
		bool _LanternOn;

		//! Current fuel in the lantern 0.0f min -> 1.0f max
		float _fuelLevel;

	public:
		//! Constructor
		Player(GameEngine::GameState* parentState,irr::core::vector3df position);
		
		//! Destructor
		~Player();
		
		//! returns the players camera
		irr::scene::ICameraSceneNode* getCamera() { return _camera; }

		//! Set the state of the lantern, will not light if no fuel.
		void toggleLantern(bool onoff);

		//! called when health <= 0
		void handleDeath();

		bool loadContent(){
			return true;
		};
		
		void update(float delta);
		
		void intitalise(){};
		
		void Player::handleMessage(const GameEngine::Message& message);

};