#pragma once
#include "GameState.h"

/*! \brief Primary Game logic for Sanctum of Shadows
 * \ingroup Game
 */
class Main_Scene : public GameEngine::GameState{

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
};