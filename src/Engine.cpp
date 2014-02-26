/*===============================================================================
  Class:   Engine
  Inherits from:  None
  Author:   Sam Serrels
  Purpose:  0000
===============================================================================*/

#include "Engine.h"
#include "EntityManager.h"
#include <iostream>

namespace GameEngine{

	Engine engine = Engine();
	KeyHandler handler = KeyHandler();

	bool Engine::initialise(){
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
	
		return true;
	}

	bool Engine::render(){
		if (!_device->getVideoDriver()->beginScene()){
			return false;
		}
		_device->getSceneManager()->drawAll();
		_device->getGUIEnvironment()->drawAll();
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
		_device->drop();
	}

	void Engine::debug(){
		EntityManager::debug();
	}
}