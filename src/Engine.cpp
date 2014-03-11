/*===============================================================================
  Class:   Engine
  Inherits from:  None
  Author:   Sam Serrels
  Purpose:  0000
===============================================================================*/

#include "Engine.h"
#include <iostream>

namespace GameEngine{

	Engine engine = Engine();
	KeyHandler handler = KeyHandler();
	const bool debug_draw_bullet = true;	
	irr::video::SMaterial debugMat;
	DebugDraw* debugDraw;

	bool Engine::initialise(){
		_run = true;
		_device = irr::createDevice(
			irr::video::EDT_DIRECT3D9, _dimensions, 16, false, true, false, &handler);
		//TODO investigate if vsync can be toggled
		if (!_device){
			std::cerr << "Error creating device" << std::endl;
			return false;
		}
		_device->setWindowCaption(_caption.c_str());

		//init ent mgmt
		if(!MessageHandler::initialise())
		{
			return false;
		}

		if(!EntityManager::initialise())
		{
			return false;
		}
		
		if(!Physics::initialise())
		{
			return false;
		}
		if(debug_draw_bullet)
		{
			//physics debug
			debugDraw = new DebugDraw(_device);
			   debugDraw->setDebugMode(
					 btIDebugDraw::DBG_DrawWireframe |
					 btIDebugDraw::DBG_DrawAabb |
					 btIDebugDraw::DBG_DrawContactPoints |
					 btIDebugDraw::DBG_DrawText |
					 //btIDebugDraw::DBG_DrawConstraintLimits |
					 btIDebugDraw::DBG_DrawConstraints //|
			   );
			  Physics::world->setDebugDrawer(debugDraw);

			   debugMat.Lighting = false;
		}



		return true;
	}

	bool Engine::loadContent(){
		if(!EntityManager::loadContent())
		{
			return false;
		}
		return true;
	}

	bool Engine::update(float delta){
		if(!EntityManager::update(delta))
		{
			return false;
		}
		if(!MessageHandler::update())
		{
			return false;
		}
		
		//2nd param is physics ticks per second.
		Physics::world->stepSimulation(delta,60);

		return true;
	}

	bool Engine::render(){
		if (!_device->getVideoDriver()->beginScene()){
			return false;
		}
		_device->getSceneManager()->drawAll();
		_device->getGUIEnvironment()->drawAll();
		
		if(debug_draw_bullet)
		{
			_device->getVideoDriver()->setMaterial(debugMat);
			_device->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
			Physics::world->debugDrawWorld();
		}

		if (!_device->getVideoDriver()->endScene()){
			return false;
		}
		return true;
	}

	void Engine::unloadContent(){
		EntityManager::unloadContent();
	}

	void Engine::shutdown(){
		EntityManager::shutdown();
		if(_device)
		{
			_device->closeDevice();
			_device = NULL;
		}
	}

	void Engine::stop(){
		_run = false;
	}
	bool Engine::run(){
		return _run;
	}

	void Engine::debug(){
		EntityManager::debug();
	}
}