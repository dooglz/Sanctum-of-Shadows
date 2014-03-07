#include "Character.h"

//this makes a geneirc character with a blank render object
void Character::intitalise(irr::core::vector3df position, irr::core::vector3df size)
{
	_walkVelocity = btScalar(600);
	if(size.getLengthSQ() == 0)
	{
		size = irr::core::vector3df(50.0f,80.0f,50.0f);
	}

	//Physics Kinematic caracter Object
	_characterC = addCharacter((btScalar)1.0f, &btVector3(position.X, position.Y, position.Z), (btScalar)size.Y/2, (btScalar)size.X/2);

	//render node
	_node = GameEngine::engine.getDevice()->getSceneManager()->addEmptySceneNode();
}

void Character::update(float delta)
{
	_xform = _ghostObject->getWorldTransform ();

	_forwardDir = _xform.getBasis()[2];
	_forwardDir.setX(-1.0f * _forwardDir.getX());//Some crazy bullet stuff results in this needing done.
	_upDir = _xform.getBasis()[1];
	_strafeDir = _xform.getBasis()[0];

	_forwardDir.normalize ();
	_upDir.normalize ();
	_strafeDir.normalize ();
}

void Character::walk(float delta)
{	
	if(_ghostObject )
	{
		btVector3 walkDirection = btVector3(0.0, 0.0, 0.0);
		btScalar walkSpeed = _walkVelocity * delta;
		
		//rotate
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
			walkDirection += _forwardDir;
		}

		if (walkback == true)
		{
			walkDirection -= _forwardDir;	
		}
		_characterC->setWalkDirection(walkDirection*walkSpeed);

		//Set the render node's position and rotation to match _ghostObject's
		//btMotionState is currently only available for rigid bodies and not Ghost Objects apperently
		if(_node)
		{
			btTransform worldTrans;
			worldTrans = _ghostObject->getWorldTransform();
			irr::core::matrix4 matr;
			worldTrans.getOpenGLMatrix(matr.pointer());
			_node->setRotation(matr.getRotationDegrees());
			_node->setPosition(matr.getTranslation());
		
		}
	}
}

btKinematicCharacterController*  Character::addCharacter(btScalar stepHeight,btVector3* characterPosition, btScalar characterHeight, btScalar characterWidth)
{
	_ghostObject = new btPairCachingGhostObject();
	btGhostPairCallback* ghostPairCallback = new btGhostPairCallback();
	GameEngine::Physics::broadPhase->getOverlappingPairCache()->setInternalGhostPairCallback(ghostPairCallback);

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

void Character::unloadContent(){
	if(_node)
	{
		_node->drop();
		_node = 0;
	}
	delete _characterC;
	_characterC = 0;
}