#include "EntityManager.h"
#pragma once
#include <iostream>
#include "Utilities.h"

namespace GameEngine{

	// Constructor
	EntityManager::EntityManager()
	{
		// The next available ID to assign to an Entity.
		int _nextID = 0;

		// A Map of every Entity, identified by ID.
		std::unordered_map<int,Entity*>_entities = std::unordered_map<int,Entity*>();

		// A Map containing lists of named entities, identified by Name.
		std::unordered_map<std::string, std::list<Entity*>> _namedEntities = std::unordered_map<std::string,std::list<Entity*>>();
	}


	// Call initialise() on all Entities.
	bool EntityManager::initialise()
	{
		std::unordered_map<int,Entity*>::iterator iter = _entities.begin();
		for(; iter != _entities.end(); ++iter)
		{
			iter->second->intitalise();
		}
		return true;
	}

	// Call loadContent() on all Entities.
	bool EntityManager::loadContent()
	{
		std::unordered_map<int,Entity*>::iterator iter = _entities.begin();
		for(; iter != _entities.end(); ++iter)
		{
			if(!iter->second->loadContent())
			{
				return false;
			}
		}
		return true;
	}


	// Call update() on all live Entities.
	bool EntityManager::update(float delta)
	{
		std::unordered_map<int,Entity*>::iterator iter = _entities.begin();
		for(; iter != _entities.end();)
		{
			if(iter->second->shouldRemove())
			{
				remove(iter);
			}
			else
			{
				if(iter->second->isAlive())
				{
					iter->second->update(delta);
				}
				++iter;
			}
		}
		return true;
	}

	// Clear all lists, will call destructor on any entities still defined.
	void EntityManager::shutdown()
	{
		std::unordered_map<int,Entity*>::iterator iter = _entities.begin();
		for(; iter != _entities.end(); ++iter)
		{
			//delete ent, free memory
			if(iter->second != nullptr )
			{
				iter->second->setID(-1);
				delete iter->second;
				iter->second = NULL;
			}
		}
		_entities.clear();
		_namedEntities.clear();
	}

	// Registers the pointer to the entity in the relevant lists.
	void EntityManager::registerEntity(Entity* newEntity)
	{
		if(newEntity->getID() == -1)
		{
			//No id currently allocated to this entity, find one.
			while (_entities.find(_nextID) != _entities.end())
			{
				//TODO add overflow protection here
				++_nextID;
			}
			newEntity->setID(_nextID++);
		}
		//Ent already has an ID, but is it already in use?
		else if(_entities.find(newEntity->getID()) != _entities.end())
		{
			std::cerr << "Error registering entity, ID" << newEntity->getID() << std::endl;
			return;
		}
		//all checks are fine, add to map
		_entities[newEntity->getID()] = newEntity;
		//now check if ent has a name
		if(newEntity->getName() != "")
		{
			auto found = _namedEntities.find(newEntity->getName());
			if(found != _namedEntities.end())
			{
				found->second.push_back(newEntity);
			}
			else
			{
				std::list<Entity*> newList;
				newList.push_back(newEntity);
				_namedEntities[newEntity->getName()] = newList;
			}
		}
	}

	//! Finds an entity in _entities, then passes the iterator to the main remove function
	bool EntityManager::remove(Entity* entity)
	{
		std::unordered_map<int,Entity*>::iterator found = _entities.find(entity->getID());
		if(found != _entities.end())
		{
			return remove(found);
		}
		return false;
	}

	// Takes an iterator from _entities, Removes entity from _entities and _namedentities, increments iterator, Does not delete the actual entity.
	bool EntityManager::remove(std::unordered_map<int,Entity*>::iterator &iter)
	{
		if(VERBOSE_lEVEL > 1)
		{
			std::cout << "Removing Entity: ID:"<<iter->first << " Name: " << iter->second->getName() << std::endl;
			std::cout << "_entities.size: " << _entities.size() << std::endl;
		}

		//does entity have a name
		if(iter->second->getName() != "")
		{
			//remove from Named_entites also
			auto found = _namedEntities.find(iter->second->getName());
			if(found != _namedEntities.end())
			{
				found->second.remove(iter->second);
			}
		}

		//Tell the entity it is no longer tracked
		iter->second->setID(-1);

		//Delete the pointer to the Entity from the main list. The iterator gets incremented
		iter = _entities.erase(iter);
		if(VERBOSE_lEVEL > 1)
		{
			std::cout << "_entities.size: " <<  _entities.size() << std::endl;
		}
		return true;
	}

	// Get Entity by ID.
	Entity* EntityManager::getEntity(int id)
	{
		auto found = _entities.find(id);
		if(found != _entities.end())
		{
			return found->second;
		}
		return 0;
	}

	// Returns a list of named entities
	std::list<Entity*>* EntityManager::getNamedEntity(const std::string& name)
	{
		auto found = _namedEntities.find(name);
		if(found != _namedEntities.end())
		{
			return &(found->second);
		}
		else
		{
			return 0;
		}
	}

	// Print debug info to std::out.
	void EntityManager::debug()
	{
		std::string str;
		std::unordered_map<int,Entity*>::iterator iter = _entities.begin();
		std::cout << "Entity Manifest" << std::endl;
		std::cout << "Total Entities: " << _entities.size() << std::endl;
		for(; iter != _entities.end(); iter++)
		{
			std::cout << iter->first << "\t" << iter->second->getName() <<"\t("
				<< iter->second->getNode()->getPosition().X << ", "
				<< iter->second->getNode()->getPosition().Y << ", "
				<< iter->second->getNode()->getPosition().Z << ")"
				<<std::endl;
		}
	}

}