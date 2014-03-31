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

	if (!GameEngine::engine.initialise())
	{
		return -1;
	}
	if (!game->init())
	{
		return -1;
	}

	//pull a pointer to the irrlicht device, we will need it every loop, not looking it up might save us a nanosecond or two.
	irr::IrrlichtDevice* device  = GameEngine::engine.getDevice();
	irr::video::IVideoDriver* driver = device->getVideoDriver();

	//Frame Timing
	irr::u32 prevTime = device->getTimer()->getRealTime();
	irr::u32 currtime;

	float delta;

	//Main Loop
	int lastFPS = -1;
	while (device->run() && GameEngine::engine.run())
	{
		currtime = device->getTimer()->getRealTime();
		delta = (currtime - prevTime) / 1000.f; // Time in seconds

		
		if (device->isWindowActive())
        {

			if(delta > 1.0f)
			{
				delta = 0.0f;
			}

			if (!GameEngine::engine.update(delta))
			{
				break;
			}

			if (!game->update(delta))
			{
				break;
			}

			if (!GameEngine::engine.render())
			{
				break;
			}
			prevTime = currtime;
			int fps = driver->getFPS();

			if (lastFPS != fps)
			{
				irr::core::stringw str = L"Sanctum Of Shadows [";
				str += driver->getName();
				str += "] FPS:";
				str += fps;
				str += " Ents:";
				str +=  game->getActiveScene()->getEntityManager()->entityCount();
				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
		}
		else
		{
			//Don't update or render while window is not active
			device->yield();
		}
	}
	delete game;
	game = NULL;
	GameEngine::engine.shutdown();
}