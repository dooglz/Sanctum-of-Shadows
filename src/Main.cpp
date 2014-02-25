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

	//pull a pointer to the irrlicht device, we will need it every loop, not looking it up might save us a nanosecond or two.
	irr::IrrlichtDevice* device  = GameEngine::engine.getDevice();

	//Frame Timing
	irr::u32 prevTime = device->getTimer()->getRealTime();
	irr::u32 currtime;
	float delta;

	//Main Loop
	while (device->run()){
		if (device->isWindowActive())
        {
			currtime = device->getTimer()->getRealTime();
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
        else
		{
          device->yield();
		}
	}

	GameEngine::engine.unloadContent();
	GameEngine::engine.shutdown();
}