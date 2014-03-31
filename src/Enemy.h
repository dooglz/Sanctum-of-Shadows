#pragma once
#include <irrlicht.h>
#include "Character.h"
#include "Player.h"

/*! \brief An Enemy.
 * \ingroup Game
 */

class Enemy:public Character{
	private:
		
		//! A reference to the player Entity
		static Player* _player;

		//! AI states of enemies
		static const enum enemyState{IDLE,COMBAT};

		//! current state
		enemyState _state;

		//! The current navigation Target.
		irr::core::vector3df _targetPosition;

		//! How close a player can get before aggro.
		float _visibleRange;

		//! How close the enemy can be to player before it can attack.
		float _combatRange;

		//! combat state logic
		void process_combat(float delta);

	public:
		//! Constructor
		Enemy(GameEngine::Scene* parentScene, irr::core::vector3df position);
		
		//! Destructor
		~Enemy(){};

		void intitalise(){};
		
		bool loadContent(){return true;};
		
		void update(float delta);
		
		void handleMessage(const GameEngine::Message& message);

		//! Set the reference to the player Entity
		static void setPlayer(Player* player);
};
