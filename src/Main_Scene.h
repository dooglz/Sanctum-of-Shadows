#pragma once
#include "GameState.h"
#include "EntityManager.h"
#include "Player.h"

/*! \brief Primary Game logic for Sanctum of Shadows
 * \ingroup Game
 */
class Main_Scene : public GameEngine::GameState{
	private:

		//! is the game over? Used for death animations
		static bool _gameover;

		//! Removes all new created Entities, resets everything to starting positions.
		void reset();

		void GameOver();

	public: 
		//! Constructor.
		Main_Scene();

		//! Destructor.
		~Main_Scene();

		bool loadContent();

		void initialize();

		void flush();

		void update(float delta);

		void render(); 

		//! The Player Entity.
		static Player* player;
};