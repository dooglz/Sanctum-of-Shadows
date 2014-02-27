#pragma once
#include "Entity.h"

namespace GameEngine{
	//TODO investigate id in constructor, nessisary?
	Entity::Entity(int id, irr::scene::ISceneNode* node, const std::string& name)
	{
		_name = name;
		_id = id;
		_node = node;
		_shouldRemove = false;
		EntityManager::registerEntity(this);
	}
	void Entity::die()
	{
		_shouldRemove = true;
	}
}