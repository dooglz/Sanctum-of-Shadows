#pragma once
#include <irrlicht.h>
#include "Message.h"
#include "MessageHandler.h"

#include "EntityManager.h"

namespace GameEngine{

	class Entity{
	protected:
		int _id;
		std::string _name;
		irr::scene::ISceneNode* _node;
		bool _alive;
		bool _shouldRemove;
		virtual void die();

	public:
		Entity(int id, irr::scene::ISceneNode* node,const std::string& name);
			virtual ~Entity(){}
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
		virtual void update(float deltaTime) = 0;
		virtual void intitalise() = 0;
		virtual bool loadContent() = 0;
		virtual void unloadContent() = 0;
		virtual void handleMessage(const Message& message){}
	};
}