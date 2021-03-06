#pragma once
#include <irrlicht.h>
#include "Message.h"
#include "MessageHandler.h"
#include "Scene.h"

namespace GameEngine{
	/*! \brief An entity has its update function called by EntityManager if it is alive, it also has a scene node attached.
	 *  \ingroup  Engine
	 */
	class Entity{
		protected:
			//! A unique int assigned by entityManager for identification.
			int _id;

			//! A string used for collecting and finding entities
			std::string _name;

			//! An irrlicht scene node associated with this entity
			irr::scene::ISceneNode* _node;

			//! Scene which this entity belongs to, used for getting the relevant Entity Manager.
			Scene* _parentScene;

			//! If _alive = false, EnityManager will not call update(), the node will still be rendered however.
			bool _alive;

			//! A flag to tell EntityManager to remove this entity from the entity List at the next loop. May cause leaks!
			bool _shouldRemove;

		public:
			//! Constructor, registers with the manager
			Entity(Scene* parentScene, irr::scene::ISceneNode* node,const std::string& name);

			//! Destructor.
			virtual ~Entity();

			//! Process per frame logic.
			virtual void update(float delta) = 0;

			//! Set all values to a default state, can be called multiple times. 
			virtual void intitalise() = 0;

			//! All resources (textures/meshes) should be loaded and assigned in this function.
			virtual bool loadContent() = 0;

			//! Receive and process a message.
			virtual void handleMessage(const Message& message){}

			//! Remove from Entity manager,  Remember to call Delete afterwards.
			virtual void remove();

			//! Returns _node.
			irr::scene::ISceneNode* getNode()
			{
				return _node;
			}
			
			//! Returns _alive.
			bool isAlive()
			{
				return _alive;
			}
			
			//! Sets _alive.
			void setAlive(bool b)
			{
				_alive = b;
			}
			
			//! Returns _id.
			int getID()
			{
				return _id;	
			}
			
			//! Sets _id.
			void setID(int id)
			{
				_id = id;
			}
			
			//! Returns _name.
			std::string getName()
			{
				return _name;	
			}
			
			//! Returns _shouldRemove.
			bool shouldRemove()
			{
				return _shouldRemove;
			}
	};
}