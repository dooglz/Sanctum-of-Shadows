#pragma once
#include <unordered_map>
#include <iostream>
#include "Entity.h"

namespace GameEngine{
	/*! \brief Tracks all Entities, used for calling update() and returning pointers
	 *  \ingroup  Engine
	 */
	class EntityManager
	{
		private:
			//! The next availbe ID to assign to an Entity.
			static int _nextID;

			//! A Map of every Entity, identified by ID.
			static std::unordered_map<int, Entity*> _entities;

			//! A Map contating lists of named entities, identified by Name.
			static std::unordered_map<std::string, std::list<Entity*>> _namedEntities;

			//! Takes an iterator from _entities, Removes entity from _entities and _namedentities, increments iterator, Does not delete the actual entity.
			static bool remove(std::unordered_map<int,Entity*>::iterator&);

			//! Constructor.
			EntityManager(){};

			//! Destructor.
			~EntityManager(){};

		public:
			//! Call initialise() on all Entities.
			static bool initialise();

			//! Call loadContent() on all Entities.
			static bool loadContent();

			//! Call update() on all live Entities.
			static bool update(float delta);

			//! Registers the pointer ot the entity in the relevant lists.
			static void registerEntity(Entity* entity);
			
			//! Finds an entity in _entities, then passes the iterator to the main remove function.
			static bool remove(Entity* entity);

			//! Get Entity by ID.
			static Entity* getEntity(int id);

			//! Returns the amount of stored entities.
			static int entityCount()
			{
				return _entities.size();
			}

			//! Returns a list of named entities
			static std::list<Entity*>* getNamedEntity(const std::string& name);

			//! clear all lists, will call destructor on any entities still defined.
			static void shutdown();

			//! Print debug info to std::out.
			static void debug();
	};
}