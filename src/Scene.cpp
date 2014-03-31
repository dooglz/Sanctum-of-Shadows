#pragma once
#include "EntityManager.h"
#include "Scene.h"

namespace GameEngine{
	EntityManager* Scene::getEntityManager()
	{
		return _entityManager;
	}

	 Scene::Scene (std::string name):_name(name)
	 {
		 _entityManager = new GameEngine::EntityManager();
	 }

}