#pragma once
#include "EntityManager.h"
#include "GameState.h"

namespace GameEngine{
	EntityManager* GameState::getEntityManager()
	{
		return _entityManager;
	}
}