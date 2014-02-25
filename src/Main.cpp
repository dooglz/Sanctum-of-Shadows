/*===============================================================================
  Author:   Sam Serrels
  Purpose:  Entry and exit point for game application.
===============================================================================*/

#pragma comment(lib,"Irrlicht")

#include "Engine.h"
#include "Game.h"
#include "SanctumOfShadows.h"
#include <iostream>

int main(){

	//initilisation
	Game * game = new SanctumOfShadows();

	GameEngine::engine.setCaption(game->getGametitle());
	GameEngine::engine.setDimensions(game->getResolution());

	if (!GameEngine::engine.initialise()){
		return -1;
	}
	if (!game->init()){
		return -1;
	}

	//Main Camera
	GameEngine::engine.setCamera(
		GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(0, 1.0f, -30.0f), irr::core::vector3df(0, 0, 0))
	);

	//Frame Timing
	irr::u32 prevTime = GameEngine::engine.getDevice()->getTimer()->getRealTime();
	irr::u32 currtime;
	float delta;

	//Main Loop
	while (GameEngine::engine.getDevice()->run()){
		currtime = GameEngine::engine.getDevice()->getTimer()->getRealTime();
		delta = (currtime - prevTime) / 1000.f; // Time in seconds

		if (!GameEngine::engine.update(delta)){
			break;
		}

		if (!game->update(delta)){
			break;
		}

		if (!GameEngine::engine.render()){
			break;
		}
		prevTime = currtime;
	}

	GameEngine::engine.unloadContent();
	GameEngine::engine.shutdown();
}