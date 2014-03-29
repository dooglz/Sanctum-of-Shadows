#pragma once
#include "Entity.h"
#include "EntityManager.h"

namespace GameEngine{
	//TODO investigate id in constructor, necessary?
	Entity::Entity(GameState* parentState, irr::scene::ISceneNode* node, const std::string& name)
	{
		_name = name;
		_id = -1;
		_node = node;
		_shouldRemove = false;
		_parentstate = parentState;
		_parentstate->getEntityManager()->registerEntity(this);
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
			_parentstate->getEntityManager()->remove(this);
		}

		if(_node != nullptr )
		{
			_node->removeAll();
			_node = NULL;
		}
	}
}