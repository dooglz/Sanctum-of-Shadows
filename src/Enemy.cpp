#include "Enemy.h"


void Enemy::intitalise(irr::core::vector3df position, Player* player)
{
	_player = player;
	irr::core::vector3df playerScale = irr::core::vector3df(50.0f,80.0f,50.0f);
	//Physics Kinematic caracter Object
	_characterC = addCharacter((btScalar)1.0f, &btVector3(position.X, position.Y, position.Z), (btScalar)50, (btScalar)30);
	//player render node
	//_playerNode = GameEngine::engine.getDevice()->getSceneManager()->addEmptySceneNode();
	_EnemyNode = GameEngine::engine.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_EnemyNode->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_stone.png"));
	_EnemyNode->setScale(playerScale);
	_EnemyNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	//player camera
}

void Enemy::update(float delta)
{	
	int n1 = rand() % 100;
	int n2 = rand() % 250;
	int n3 = rand() % 100;


	if(_ghostObject ){
		///set walkDirection for our Enemy
		btTransform xform;
		xform = _ghostObject->getWorldTransform ();

		btVector3 forwardDir = xform.getBasis()[2];
		forwardDir.setX(-1.0f * forwardDir.getX());//Some crazy bullet stuff results in this needing done.
		btVector3 upDir = xform.getBasis()[1];
		btVector3 strafeDir = xform.getBasis()[0];
		forwardDir.normalize ();
		upDir.normalize ();
		strafeDir.normalize ();

		btVector3 walkDirection = btVector3(0.0, 0.0, 0.0);
		btScalar walkVelocity = btScalar(1.1) * 600.0;
		btScalar walkSpeed = walkVelocity * delta;
		walkleft=false;
		walkright=false;
		walkforward = false;
		float angleToplayer =  forwardDir.angle(GameEngine::Physics::irrVec3ToBtVec3 ((_player->getNode()->getPosition() - _EnemyNode->getPosition())));

		if(angleToplayer > 1)
		{
			angleToplayer =1;
		}
		if(angleToplayer < -1)
		{
			angleToplayer = -1;
		}
		
		angleToplayer = acos(angleToplayer);
		float crossToplayer = forwardDir.cross(GameEngine::Physics::irrVec3ToBtVec3 ((_player->getNode()->getPosition() - _EnemyNode->getPosition()))).getY(); 
		if((_player->getNode()->getPosition() - _EnemyNode->getPosition()).getLength() < 300.0f )
		{
			std::cout << "player is near: " <<std::endl;
		
			if(crossToplayer < 0)
			{
				walkleft=true;
			}else
			{
				walkright = true;
			}
			if(angleToplayer < 60)
			{
				walkforward = true;
			}
			else
			{
				walkforward = false;
			}

		}

		/*
		if(n2 < 2)
		{
			if (n1 < 40)
			{
			walkforward = true;
			
			}
			else 
			{
				walkforward = false;
			}
			if(n3 < 40)
			{
				walkleft = true;
			}
			else
			{
				walkleft = false;
			}
		}
		*/

		//rotate the enemy when these are called
		if (walkleft == true)
		{
			btMatrix3x3 orn = _ghostObject->getWorldTransform().getBasis();
			orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),-2.0f*delta));
			_ghostObject->getWorldTransform ().setBasis(orn);
		}

		if (walkright == true)
		{
			btMatrix3x3 orn = _ghostObject->getWorldTransform().getBasis();
			orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),5.0f*delta));
			_ghostObject->getWorldTransform ().setBasis(orn);
		}

		if (walkforward == true)
		{
			walkDirection += forwardDir;
		}

		/*if (GameEngine::handler.keyDown(irr::KEY_KEY_S))
		{
			walkDirection -= forwardDir;	
		}*/
		_characterC->setWalkDirection(walkDirection*walkSpeed);

		//Set the render node's position and rotation to match _ghostObject's
		//btMotionState is currently only available for rigid bodies and not Ghost Objects apperently
		if(_EnemyNode)
		{
			btTransform worldTrans;
			worldTrans = _ghostObject->getWorldTransform();
			irr::core::matrix4 matr;
			worldTrans.getOpenGLMatrix(matr.pointer());
			_EnemyNode->setRotation(matr.getRotationDegrees());
			_EnemyNode->setPosition(matr.getTranslation());
		
		}
	}
}

btKinematicCharacterController*  Enemy::addCharacter(btScalar stepHeight,btVector3* characterPosition, btScalar characterHeight, btScalar characterWidth)
{
	_ghostObject = new btPairCachingGhostObject();
	GameEngine::Physics::broadPhase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

	btConvexShape* characterShape = new btCapsuleShape(characterWidth, characterHeight);
	btTransform trans;

	trans.setIdentity();
	btScalar physicsWorldScaling2 = 0.1f;

	trans.setOrigin(*characterPosition);

	_ghostObject->setWorldTransform(trans);

	_ghostObject->setCollisionShape(characterShape);
	//ghostObject->setCollisionFlags(ghostObject->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	_ghostObject->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);

	btKinematicCharacterController*  character = new btKinematicCharacterController (_ghostObject, characterShape, stepHeight, 1);
   
	GameEngine::Physics::world->addCollisionObject(_ghostObject, GameEngine::Physics::E_Actor,GameEngine::Physics::E_ActorGroup);
	//GameEngine::Physics::world->addCollisionObject(ghostObject,btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);

	GameEngine::Physics::world->addCharacter(character);

	return character;
};

bool Enemy::loadContent()
{
	return true;
}

void Enemy::unloadContent()
{

}