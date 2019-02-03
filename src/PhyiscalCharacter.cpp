#include "PhysicalCharacter.h"

PhysicalCharacter::PhysicalCharacter(GameEngine::Scene* parentScene,const std::string& name):Character(parentScene,name){}

//! Creates the controller and adds a blank scene node.
void PhysicalCharacter::intitalise(irr::core::vector3df position, irr::core::vector3df size)
{
	_position = position;
	_walkSpeed = 6.0f;
	_rotateSpeed = 5.0f;

	if(size.getLengthSQ() == 0)
	{
		size = irr::core::vector3df(50.0f,80.0f,50.0f);
	}

	//Physics Kinematic character Object
	_characterC = addbtKinematicCharacterController((btScalar)1.0f, &btVector3(position.X, position.Y, position.Z), (btScalar)size.Y/2, (btScalar)size.X/2);

	//render node
	_node = GameEngine::engine.getDevice()->getSceneManager()->addEmptySceneNode();
}

//! Recalculate position transforms and direction vectors, call this before Walk.
void PhysicalCharacter::update(float delta)
{
	_xform = _ghostObject->getWorldTransform ();

	_forwardDir = _xform.getBasis()[2];
	_forwardDir.setX(-1.0f * _forwardDir.getX());
	_forwardDir.normalize ();

	_upDir = _xform.getBasis()[1];
	_upDir.normalize ();

	_strafeDir = _xform.getBasis()[0];
	_strafeDir.normalize ();
}

//! Move based on the walk flags.
void PhysicalCharacter::walk(float delta)
{	
	if(_ghostObject )
	{
		btVector3 walkDirection = btVector3(0.0, 0.0, 0.0);
		btScalar walkSpeed = btScalar(_walkSpeed);
		
		//rotate (needs delta as it transforms directly)
		if (walkleft == true)
		{
			btMatrix3x3 orn = _ghostObject->getWorldTransform().getBasis();
			orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),-1.0f * _rotateSpeed * delta));
			_ghostObject->getWorldTransform ().setBasis(orn);
		}

		if (walkright == true)
		{
			btMatrix3x3 orn = _ghostObject->getWorldTransform().getBasis();
			orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0), _rotateSpeed * delta));
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

		if (_characterC != nullptr )
		{
			_characterC->setWalkDirection(walkDirection*walkSpeed);
		}

		//Set the render node's position and rotation to match _ghostObject's
		//btMotionState is currently only available for rigid bodies and not Ghost Objects
		if(_node)
		{
			btTransform worldTrans;
			worldTrans = _ghostObject->getWorldTransform();
			irr::core::matrix4 matr;
			worldTrans.getOpenGLMatrix(matr.pointer());
			_node->setRotation(matr.getRotationDegrees());
			_node->setPosition(matr.getTranslation());
			_position = matr.getTranslation();
		}
	}
}

//! Create a new btKinematicCharacterController*.
btKinematicCharacterController*  PhysicalCharacter::addbtKinematicCharacterController(btScalar stepHeight,btVector3* characterPosition, btScalar characterHeight, btScalar characterWidth)
{
	_ghostObject = new btPairCachingGhostObject();
	btGhostPairCallback* ghostPairCallback = new btGhostPairCallback();
	GameEngine::Physics::broadPhase->getOverlappingPairCache()->setInternalGhostPairCallback(ghostPairCallback);

	btConvexShape* characterShape = new btCapsuleShape(characterWidth, characterHeight);
	btTransform trans;

	trans.setIdentity();
	//I have absolutly no idea why this line is nessisary
	btScalar physicsWorldScaling2 = 0.1f;

	trans.setOrigin(*characterPosition);
	_ghostObject->setWorldTransform(trans);

	_ghostObject->setCollisionShape(characterShape);
	//ghostObject->setCollisionFlags(ghostObject->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	_ghostObject->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);

	btKinematicCharacterController*  character = new btKinematicCharacterController (_ghostObject, characterShape, stepHeight,btVector3(1,0,0));
   
	GameEngine::Physics::world->addCollisionObject(_ghostObject, GameEngine::Physics::E_Actor,GameEngine::Physics::E_ActorGroup);
	//GameEngine::Physics::world->addCollisionObject(ghostObject,btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);

	GameEngine::Physics::world->addCharacter(character);
	
	return character;
};

PhysicalCharacter::~PhysicalCharacter()
{
	if (_characterC != nullptr )
	{
		GameEngine::Physics::world->removeCharacter(_characterC);
		delete _characterC;
		_characterC = NULL;
	}
	if (_ghostObject != nullptr )
	{
		GameEngine::Physics::world->removeCollisionObject(_ghostObject);
		delete _ghostObject;
		_ghostObject = NULL;
	}
}