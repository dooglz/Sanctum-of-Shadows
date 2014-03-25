/**
 * \defgroup Game Game Specific Classes
 */

#pragma once
#include "Engine.h"
#include "Game.h"
#include "Player.h"

/*! \brief Primary Game logic for Sanctum of Shadows
 * \ingroup Game
 */
class SanctumOfShadows:public Game{

	public: 

		//! States the game can be in.
		static const enum state {RUN,PAUSE,GAEMOVER,MENU};

	private:

		//! Removes all new created Entities, resets everything to starting positions.
		void reset();

		//! The current game state.
		state _state;

		//! is the game over? Used for death animations
		static bool _gameover;

	public:

		//! Constructor.
		SanctumOfShadows(){
			_gameTitle = L"SanctumOfShadows";
			_resolution  = irr::core::dimension2d<irr::u32>(1280, 720);
		};

		//! Destructor.
		~SanctumOfShadows();

		//! The Player Entity.
		static Player* player;

		//! Creates Required Entities.
		bool init();

		//! Run per-frame game logic.
		bool update(float delta);

		//! Move to Gameover State.
		static void GameOver();

		//! Returns the current game state.
		state getState(){
			return _state;
		}

};


