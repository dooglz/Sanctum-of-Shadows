#pragma once
#include <unordered_map>
#include "Entity.h"

namespace GameEngine{
	/*! \brief Tracks all Entities, used for calling update() and returning pointers
	 *  \ingroup  Engine
	 */
	class EntityManager
	{
		private:
			//! The next available ID to assign to an Entity.
			int _nextID;

			//! A Map of every Entity, identified by ID.
			std::unordered_map<int, Entity*> _entities;

			//! A Map containing lists of named entities, identified by Name.
			std::unordered_map<std::string, std::list<Entity*>> _namedEntities;

			//! Takes an iterator from _entities, Removes entity from _entities and _namedentities, increments iterator, Does not delete the actual entity.
			bool remove(std::unordered_map<int,Entity*>::iterator&);

		public:
			
			//! Constructor.
			EntityManager();

			//! Destructor.
			~EntityManager(){};

			//! Call initialise() on all Entities.
			bool initialise();

			//! Call loadContent() on all Entities.
			bool loadContent();

			//! Call update() on all live Entities.
			bool update(float delta);

			//! Registers the pointer to the entity in the relevant lists.
			void registerEntity(Entity* entity);
			
			//! Finds an entity in _entities, then passes the iterator to the main remove function.
			bool remove(Entity* entity);

			//! Get Entity by ID.
			Entity* getEntity(int id);

			//! Returns the amount of stored entities.
			size_t entityCount()
			{
				return _entities.size();
			}

			//! Returns a list of named entities
			std::list<Entity*>* getNamedEntity(const std::string& name);

			//! Clear all lists, will call destructor on any entities still defined.
			void shutdown();

			//! Print debug info to std::out.
			void debug();
	};
}