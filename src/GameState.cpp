#pragma once
#include "EntityManager.h"
#include "GameState.h"

namespace GameEngine{
	EntityManager* GameState::getEntityManager()
	{
		return _entityManager;
	}

	 GameState::GameState (std::string name):_name(name)
	 {
		 _entityManager = new GameEngine::EntityManager();
	 }

}