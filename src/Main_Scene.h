#pragma once
#include "Scene.h"
#include "EntityManager.h"
#include "Player.h"

/*! \brief Primary Game logic for Sanctum of Shadows
 * \ingroup Game
 */
class Main_Scene : public GameEngine::Scene{
	private:

		//! is the game over? Used for death animations
		static bool _gameover;

		//! is the game won.
		static bool _gamewon;

		//! is the game paused.
		static bool _gamepaused;

		//! DEBUG resets stuff, TODO remove for release
		void reset();

		//! Handle the loose scenario
		void GameOver();

		//! Handle the win scenario
		void GameWon();

	public: 
		//! Constructor.
		Main_Scene();

		//! Destructor.
		~Main_Scene();

		bool loadContent();

		void initialize();

		void flush();

		void update(float delta);

		//! The Player Entity.
		static Player* player;
};