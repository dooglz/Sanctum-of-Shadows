#pragma once
#include <btBulletCollisionCommon.h>
#include "Entity.h"

namespace GameEngine{

	class PhysicalEntity: public Entity{
	protected:
		btRigidBody* _rigidBody;
		btVector3 _position;
	public:
		PhysicalEntity(int id, irr::scene::ISceneNode* node,const std::string& name):Entity(id,node,name){}
		virtual ~PhysicalEntity(){}
		void update(float delta);

		btRigidBody* getRB() 
		{
			return _rigidBody;
		}
		void setRB(btRigidBody* value)
		{
			_rigidBody = value;
		}
	};

}