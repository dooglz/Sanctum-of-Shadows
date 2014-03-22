/*===============================================================================
  Author:   Sam Serrels
  Purpose:  Entry and exit point for game application.
===============================================================================*/

#pragma comment(lib,"Irrlicht")
//Bullet
#if defined(DEBUG) | defined(_DEBUG)
	#pragma comment(lib, "BulletCollision_Debug")
	#pragma comment(lib, "BulletDynamics_Debug")
	#pragma comment(lib, "LinearMath_Debug")
#else
	#pragma comment(lib, "BulletCollision")
	#pragma comment(lib, "BulletDynamics")
	#pragma comment(lib, "LinearMath")
#endif

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
	irr::video::IVideoDriver* driver = device->getVideoDriver();


	//Frame Timing
	irr::u32 prevTime = device->getTimer()->getRealTime();
	irr::u32 currtime;
	float delta;
	float updateDelta;
	float renderDelta;

	//Main Loop
	int lastFPS = -1;
	while (device->run() && GameEngine::engine.run()){
		if (device->isWindowActive())
        {

			currtime = device->getTimer()->getRealTime();
			delta = (currtime - prevTime) / 1000.f; // Time in seconds
			if(delta > 1.0f)
			{
				delta = 0.0f;
			}

			if (!GameEngine::engine.update(delta)){
				break;
			}

			if (!game->update(delta)){
				break;
			}

			updateDelta = (float)(device->getTimer()->getRealTime() - currtime);

			if (!GameEngine::engine.render()){
				break;
			}

			renderDelta = (device->getTimer()->getRealTime() - updateDelta);

			prevTime = currtime;
			//GameEngine::engine.setCaption(game->getGametitle()+L" | "+(std::to_wstring(1000*currtime)));
			int fps = driver->getFPS();

			if (lastFPS != fps)
			{
				irr::core::stringw str = L"Sanctum Of Shadows [";
				str += driver->getName();
				str += "] FPS:";
				str += fps;
				str += " Ents:";
				str += GameEngine::EntityManager::entityCount();
				str += " render:";
				str += (renderDelta/(renderDelta+updateDelta))*100.0f;
				str += " Update:";
				str += (updateDelta/(renderDelta+updateDelta))*100.f;
				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}

		}
		else
		{
			device->yield();
		}
	}
	delete game;
	game = NULL;
	GameEngine::engine.unloadContent();
	GameEngine::engine.shutdown();
}