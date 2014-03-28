/**
 * \defgroup Game Game Specific Classes
 */

#pragma once
#include "Engine.h"
#include "Game.h"
//#include "Player.h"

/*! \brief Primary Game logic for Sanctum of Shadows
 * \ingroup Game
 */
class SanctumOfShadows:public Game{

	public: 

		//! States the game can be in.
		static const enum state {RUN,PAUSE,GAEMOVER,MENU};

	private:

		//! The current game state.
		state _state;

	public:
		static GameEngine::GameState* gameState;

		//! Constructor.
		SanctumOfShadows(){
			_gameTitle = L"SanctumOfShadows";
			_resolution  = irr::core::dimension2d<irr::u32>(1280, 720);
		};

		//! Destructor.
		~SanctumOfShadows();

		//! Creates Required Entities.
		bool init();

		//! Run per-frame game logic.
		bool update(float delta);

};


