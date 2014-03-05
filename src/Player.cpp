#include "Player.h"

void Player::intitalise(irr::core::vector3df position)
{
	irr::core::vector3df playerScale = irr::core::vector3df(60.0f,100.0f,60.0f);
	//Physics Kinematic caracter Object
	_characterC = addCharacter((btScalar)1.0f, &btVector3(position.X, position.Y, position.Z), (btScalar)50, (btScalar)30);
	//player render node
	//_playerNode = GameEngine::engine.getDevice()->getSceneManager()->addEmptySceneNode();
	_playerNode = GameEngine::engine.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_playerNode->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_stone.png"));
	_playerNode->setScale(playerScale);
	_playerNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	//player camera
	_camera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNode(_playerNode,irr::core::vector3df(0,0,0));
	_camera->bindTargetAndRotation(true);
}

void Player::update(float delta)
{	
	if(_ghostObject ){
		///set walkDirection for our character
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

		//rotate view
		if (GameEngine::handler.keyDown(irr::KEY_KEY_A))
		{
			btMatrix3x3 orn = _ghostObject->getWorldTransform().getBasis();
			orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),-5.0f*delta));
			_ghostObject->getWorldTransform ().setBasis(orn);
		}

		if (GameEngine::handler.keyDown(irr::KEY_KEY_D))
		{
			btMatrix3x3 orn = _ghostObject->getWorldTransform().getBasis();
			orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),5.0f*delta));
			_ghostObject->getWorldTransform ().setBasis(orn);
		}

		if (GameEngine::handler.keyDown(irr::KEY_KEY_W))
		{
			walkDirection += forwardDir;
		}

		if (GameEngine::handler.keyDown(irr::KEY_KEY_S))
		{
			walkDirection -= forwardDir;	
		}
		_characterC->setWalkDirection(walkDirection*walkSpeed);

		//Set the render node's position and rotation to match _ghostObject's
		//btMotionState is currently only available for rigid bodies and not Ghost Objects apperently
		if(_playerNode)
		{
			btTransform worldTrans;
			worldTrans = _ghostObject->getWorldTransform();
			irr::core::matrix4 matr;
			worldTrans.getOpenGLMatrix(matr.pointer());
			_playerNode->setRotation(matr.getRotationDegrees());
			_playerNode->setPosition(matr.getTranslation());
			// Follow with the camera
			if(_camera)
			{
				_camera->setTarget( _playerNode->getPosition()+GameEngine::Physics::btVecToirrVec3(forwardDir) );
			}
		}
	}
}

btKinematicCharacterController*  Player::addCharacter(btScalar stepHeight,btVector3* characterPosition, btScalar characterHeight, btScalar characterWidth)
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

bool Player::loadContent()
{
	return true;
}

void Player::unloadContent()
{

}