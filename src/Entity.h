#pragma once
#include <irrlicht.h>
#include "Message.h"
#include "MessageHandler.h"
#include "EntityManager.h"

namespace GameEngine{
	/*! \brief An entity has its update function called by entitymanager if it is alive, it also has a scenenode attached.
	 *  \ingroup  Engine
	 */
	class Entity{
		protected:
			//A unique int assigned by entityManager for identification.
			int _id;

			//! A string used for collecting and finding entities
			std::string _name;

			//! An irrlicht scene node assosiated with this entity
			irr::scene::ISceneNode* _node;

			//! If _alive = false, EnityManager will not call update(), the node will still be rendered however.
			bool _alive;

			//! A flag to tell EntityManager to remove this entity from the entity List.
			bool _shouldRemove;

			//TODO call this remove()
			//! sets _shouldremove to true, all final gamelogic for this Entity should be in here.
			virtual void die();

		public:
			//! Constructor
			Entity(int id, irr::scene::ISceneNode* node,const std::string& name);

			//! Destructor.
			virtual ~Entity(){}

			virtual void update(float deltaTime) = 0;

			//! Set all values to a default state, can be called multiple times. 
			virtual void intitalise() = 0;

			//! All resources (textures/meshes) should be loaded and assigned in this function.
			virtual bool loadContent() = 0;

			//TODO Not nessisary, migrate to destructor
			virtual void unloadContent() = 0;

			//! Receive and process a message.
			virtual void handleMessage(const Message& message){}

			//Getters and setters
			irr::scene::ISceneNode* getNode()
			{
				return _node;
			}

			bool isAlive()
			{
				return _alive;
			}

			void setAlive(bool b)
			{
				_alive = b;
			}

			int getID()
			{
				return _id;	
			}

			void setID(int id)
			{
				_id = id;
			}

			std::string getName()
			{
				return _name;	
			}

			void setID(std::string name)
			{
				_name = name;
			}

			bool shouldRemove()
			{
				return _shouldRemove;
			}
	};
}