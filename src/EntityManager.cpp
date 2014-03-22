#include "EntityManager.h"

namespace GameEngine{

	//init our static attributes
	int EntityManager::_nextID = 0;
	//Entities holds a pointer to ALL entities.
	std::unordered_map<int,Entity*> EntityManager::_entities = std::unordered_map<int,Entity*>();
	//namedEntites holds a copy of a pointer to all ents with a set name.
	std::unordered_map<std::string, std::list<Entity*>> EntityManager::_namedEntities = std::unordered_map<std::string,std::list<Entity*>>();
	//blank con/destructor
	EntityManager::EntityManager(){}
	EntityManager::~EntityManager(){}

	bool EntityManager::initialise()
	{
		std::unordered_map<int,Entity*>::iterator iter = _entities.begin();
		for(; iter != _entities.end(); ++iter)
		{
			iter->second->intitalise();
		}
		return true;
	}

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

	void EntityManager::unloadContent()
	{
		std::unordered_map<int,Entity*>::iterator iter = _entities.begin();
		for(; iter != _entities.end(); ++iter)
		{
			iter->second->unloadContent();
		}
	}

	bool EntityManager::update(float delta)
	{
		//we don't update named entites???
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


	void EntityManager::shutdown()
	{
		std::unordered_map<int,Entity*>::iterator iter = _entities.begin();
		for(; iter != _entities.end(); ++iter)
		{
			//delete ent, free memeory
			delete iter->second;
			//set pointer to null
			iter->second = 0;
		}
		_entities.clear();
		_namedEntities.clear();
	}

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

	void EntityManager::removeEntity(Entity* entity)
	{
		auto found = _entities.find(entity->getID());
		if(found != _entities.end())
		{
			_entities.erase(found);
		}
	}

	bool EntityManager::remove(Entity* entity)
	{
		std::unordered_map<int,Entity*>::iterator found = _entities.find(entity->getID());
		if(found != _entities.end())
		{
			return remove(found);
		}
		return false;
	}

	bool EntityManager::remove(std::unordered_map<int,Entity*>::iterator &iter)
	{
		std::cout << "Removing Entity: ID:"<<iter->first << " Name: " << iter->second->getName() << std::endl;
		std::cout << _entities.size() << std::endl;

		//does entity have a name
		if(iter->second->getName() != "")
		{
			//remove from Named_entites also
			auto found = _namedEntities.find(iter->second->getName());
			if(found != _namedEntities.end())
			{
				std::cout << found->second.size()<< std::endl;
				found->second.remove(iter->second);
				std::cout << found->second.size()<< std::endl;
			}
		}
		//Delete the entity itsef, calling it's destructor then freeing the memory.
		delete iter->second;
		//Delete the pointer to the Entity from the main list.
		iter = _entities.erase(iter);
		std::cout << _entities.size() << std::endl;
		return true;
	}

	Entity* EntityManager::getEntity(int id)
	{
		auto found = _entities.find(id);
		if(found != _entities.end())
		{
			return found->second;
		}
		return 0;
	}

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