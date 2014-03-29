#include "SanctumOfShadows.h"

#include "Level.h"
#include "Beacon.h"
#include <btBulletDynamicsCommon.h>
#include "Main_Scene.h"
#include "Menu_Scene.h"

// Creates Required Entities.
bool SanctumOfShadows::init(){
	std::wcout <<  _gameTitle << " Game code init" << std::endl;

	_gameState = new Main_Scene();
	_menuState = new Menu_Scene();
	addState(_gameState);
	addState(_menuState);

	_LoadingImg = GameEngine::engine.getDevice()->getGUIEnvironment()->addImage(irr::core::rect<irr::s32>(300,400,600,700),0);
	//TODO checks this loads.
	_LoadingImg ->setImage(GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_radius.png"));
	
	changeState("menu");

	return true;
}

// Run per-frameState Independent game logic.
bool SanctumOfShadows::update(float delta){
	
	processStates();
	
	if(GameEngine::handler.keyFired(irr::KEY_ESCAPE))
	{
		GameEngine::engine.stop();
	}

	if(GameEngine::handler.keyFired(irr::KEY_F8))
	{
		GameEngine::engine.setBulletDebugDrawing(!GameEngine::engine.getBulletDebugDrawing());
	}
	
	if(_stateLoaded)
	{
		_activeState->update(delta);
	}

	return true;
}

// Destructor
SanctumOfShadows::~SanctumOfShadows()
{

}
