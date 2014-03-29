#pragma once
#include <irrlicht.h>
#include "Character.h"
#include "Player.h"

/*! \brief An Enemy.
 * \ingroup Game
 */

class Enemy:public Character{
	private:
		static Player* _player;
		irr::core::vector3df targetPosition;

	public:
		//! Constructor
		Enemy(GameEngine::GameState* parentState, irr::core::vector3df position);
		
		//! Destructor
		~Enemy(){};

		void intitalise(){};
		
		bool loadContent(){return true;};
		
		void update(float delta);
		
		void handleMessage(const GameEngine::Message& message);

		static void setPlayer(Player* player);
};
