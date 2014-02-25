#pragma once

#include <unordered_map>
#include <iostream>
#include "Entity.h"

namespace GameEngine{

	class EntityManager
	{
		private:
			static int _nextID;
			static std::unordered_map<int, Entity*> _entities;
			static std::unordered_map<std::string, std::list<Entity*>> _namedEntities;
			static bool remove(Entity* entity);
			static bool remove(std::unordered_map<int,Entity*>::iterator&);
			EntityManager();
			~EntityManager();
		public:
			static bool initialise();
			static bool loadContent();
			static bool update(float delta);
			static void unloadContent();
			static void registerEntity(Entity* entity);
			static void removeEntity(Entity* entity);
			static Entity* getEntity(int id);
			static std::list<Entity*>* getNamedEntity(const std::string& name);
			static void shutdown();
			static void debug();
	};
}