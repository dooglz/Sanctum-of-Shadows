#pragma once
#include "GameState.h"

/*! \brief Main Menu Scene
 * \ingroup Game
 */
class Menu_Scene : public GameEngine::GameState{
	private:

	public: 
		//! Constructor.
		Menu_Scene();

		//! Destructor.
		~Menu_Scene();

		bool loadContent();

		void initialize();

		void flush();

		void update(float delta);

		void render(); 
};