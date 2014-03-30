#pragma once
#include "Entity.h"
#include "EntityManager.h"

namespace GameEngine{
	//TODO investigate id in constructor, necessary?
	Entity::Entity(Scene* parentScene, irr::scene::ISceneNode* node, const std::string& name)
	{
		_name = name;
		_id = -1;
		_node = node;
		_shouldRemove = false;
		_parentScene = parentScene;
		_parentScene->getEntityManager()->registerEntity(this);
	}
	void Entity::die()
	{
		_shouldRemove = true;
	}

	Entity::~Entity()
	{
		//IF id != 1, the manager is still tracking us
		if(_id != -1)
		{
			_parentScene->getEntityManager()->remove(this);
		}

		if(_node != nullptr )
		{
			_node->remove();
			_node = NULL;
		}
	}
}