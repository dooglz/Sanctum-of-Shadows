#include "SanctumOfShadows.h"

#include "Level.h"
#include "Beacon.h"
#include <btBulletDynamicsCommon.h>
#include "Main_Scene.h"

GameEngine::GameState* SanctumOfShadows::gameState;

// Creates Required Entities.
bool SanctumOfShadows::init(){

	gameState = new Main_Scene();
	_activeState = gameState;
	gameState->initialize();

	std::wcout <<  _gameTitle << " Game code init" << std::endl;
	return true;
}

// Run per-frame game logic.
bool SanctumOfShadows::update(float delta){

	if(GameEngine::handler.keyFired(irr::KEY_ESCAPE))
	{
		GameEngine::engine.stop();
	}

	if(GameEngine::handler.keyFired(irr::KEY_F8))
	{
		GameEngine::engine.setBulletDebugDrawing(!GameEngine::engine.getBulletDebugDrawing());
	}

	gameState->update(delta);

	return true;
}

// Destructor
SanctumOfShadows::~SanctumOfShadows()
{
	delete gameState;
	gameState = NULL;
}
