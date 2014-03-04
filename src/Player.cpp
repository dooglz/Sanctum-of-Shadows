#include "Player.h"



void Player::intitalise(irr::core::vector3df position)
{
	irr::core::vector3df playerScale = irr::core::vector3df(60.0f,100.0f,60.0f);
	//player render node
	_playerNode = GameEngine::engine.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_playerNode->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_stone.png"));
	_playerNode->setScale(playerScale);
	_playerNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	//player Rigib body
	btVector3 halfExtends(playerScale.X*0.5f,playerScale.Y*0.5f,playerScale.Z*0.5f);
	btCollisionShape* playerShape = new btBoxShape(halfExtends);
	//Link physics and render with MotionState
	GameEngine::MotionState* playerfallMotionState = new GameEngine::MotionState(btTransform(btQuaternion(0.0, 0.0, 0.0, 1.0), btVector3(position.X, position.Y, position.Z)), _playerNode);
	btScalar playerMass = 60.0;
	btVector3 playerInertia(0.0, 0.0, 0.0);
	playerShape->calculateLocalInertia(playerMass, playerInertia);
	btRigidBody::btRigidBodyConstructionInfo playerRigidBodyCI(playerMass, playerfallMotionState, playerShape, playerInertia);
	btRigidBody* _playerRB = new btRigidBody(playerRigidBodyCI);
	GameEngine::Physics::world->addRigidBody(_playerRB,GameEngine::Physics::E_Riggid,GameEngine::Physics::E_RiggidGroup);
	//Prevent sleeping
	_playerRB->setActivationState(DISABLE_DEACTIVATION);

	_camera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNode(_playerNode,irr::core::vector3df(0,0,0));
	_camera->bindTargetAndRotation(true);

	_characterC = addCharacter((btScalar)1.0f, &btVector3(position.X, position.Y, position.Z), (btScalar)50, (btScalar)30);
	
}

bool Player::loadContent()
{
	return true;
}

void Player::unloadContent()
{

}


void Player::update(float delta)
{

	_physicsMesh->getRB()->applyForce( btVector3(100 , 0 ,0 ), btVector3(0 , 0 ,0 ));

	//_physicsMesh->getRB()->applyCentralForce( btVector3(0 ,0 ,500 ));
	//_physicsMesh->getRB()->applyTorque(btVector3(0,500,0));
	if(GameEngine::handler.keyDown(irr::KEY_KEY_W))
	{
		_physicsMesh->getRB()->applyForce(btVector3(500,0,0), btVector3(0,0,0));
		_physicsMesh->getRB()->setAngularFactor(btVector3(0, 0, 0));
	}
	
	if(GameEngine::handler.keyDown(irr::KEY_KEY_S))
	{
		_physicsMesh->getRB()->applyForce(btVector3(-500,0,0), btVector3(0,0,0));
		_physicsMesh->getRB()->setAngularFactor(btVector3(0, 0, 0));
	}
	if(GameEngine::handler.keyDown(irr::KEY_RIGHT))
	{
		_physicsMesh->getRB()->applyTorque(btVector3(0,5000,0));
	}

	btVector3 angles = _physicsMesh->getRB()->getAngularFactor();
	_physicsMesh->getRB()->setAngularFactor(btVector3(0, angles.getY(), 0));
	_camera->setRotation(_physicsMesh->getNode()->getRotation());

}


void Player::update2(float delta)
{

		btRigidBody* m_ghostObject = _physicsMesh->getRB();
		///set walkDirection for our character
		btTransform xform;
		xform = m_ghostObject->getWorldTransform ();

		btVector3 forwardDir = xform.getBasis()[2];
	//	printf("forwardDir=%f,%f,%f\n",forwardDir[0],forwardDir[1],forwardDir[2]);
		btVector3 upDir = xform.getBasis()[1];
		btVector3 strafeDir = xform.getBasis()[0];
		forwardDir.normalize ();
		upDir.normalize ();
		strafeDir.normalize ();

		btVector3 walkDirection = btVector3(0, 0, 0);
		btScalar walkVelocity = btScalar(1.1) * 4.0; // 4 km/h -> 1.1 m/s
		btScalar walkSpeed = walkVelocity * delta;

		//rotate view
		if (GameEngine::handler.keyDown(irr::KEY_LEFT))
		{
			btMatrix3x3 orn = m_ghostObject->getWorldTransform().getBasis();
			orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),0.01));
			m_ghostObject->getWorldTransform ().setBasis(orn);
		}

		if (GameEngine::handler.keyDown(irr::KEY_RIGHT))
		{
			btMatrix3x3 orn = m_ghostObject->getWorldTransform().getBasis();
			orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),-0.01));
			m_ghostObject->getWorldTransform ().setBasis(orn);
		}

		if (GameEngine::handler.keyDown(irr::KEY_UP))
			walkDirection += forwardDir;

		if (GameEngine::handler.keyDown(irr::KEY_DOWN))
			walkDirection -= forwardDir;	

		m_ghostObject->applyCentralImpulse(walkDirection);
				//_physicsMesh->getRB()->setAngularFactor(btVector3(0, 0, 0));

		//m_character->setWalkDirection(btVector3(1, 1, 1));
		std::cout << std::endl;
			_camera->setRotation(_physicsMesh->getNode()->getRotation());

}

void Player::update3(float delta)
{
	if(GameEngine::handler.keyDown(irr::KEY_RIGHT))
	{
		_playerRB->applyTorque(btVector3(0,50000,0));
	}

	bool firstUpdate = true;
	bool CursorControl = true;
	bool NoVerticalMovement= true;
	float MoveSpeed = 1000.0f;


	// If the camera isn't the active camera, and receiving input, then don't process it.
	if(!_camera->isInputReceiverEnabled())
	{
			return;
	}

	irr::scene::ISceneManager * smgr = _camera->getSceneManager();
	/*      if(smgr && smgr->getActiveCamera() != camera)
	{
			return;
	}*/

	// get time
	irr::f32 timeDiff = (delta);

	// update position
	irr::core::vector3df pos = _camera->getPosition();

	// Update rotation
	irr::core::vector3df target = (_camera->getTarget() - _camera->getAbsolutePosition());
	target = GameEngine::Physics::btVecToirrVec3(_playerRB->getWorldTransform().getBasis()[2].normalize());
	irr::core::vector3df relativeRotation = target.getHorizontalAngle();
	   
	if (CursorControl)
	{

	}

	// set target

	target.set(0,0, irr::core::max_(1.f, pos.getLength()));
        
	irr::core::vector3df movedir = target;

	irr::core::matrix4 mat;
	mat.setRotationDegrees(irr::core::vector3df(relativeRotation.X, relativeRotation.Y, 0));
	mat.transformVect(target);

	//cout<<"B: "<<movedir.X<<" "<<movedir.Y<<" "<<movedir.Z<<endl;
	if (NoVerticalMovement)
	{
			mat.setRotationDegrees(irr::core::vector3df(0, relativeRotation.Y, 0));
			mat.transformVect(movedir);
			//cout<<"C: "<<movedir.X<<" "<<movedir.Y<<" "<<movedir.Z<<endl;
	}
	else
	{
			movedir = target;
	}

	movedir.normalize();

	movedir.Y = 0;
	//body->getBodyPtr()->clearForces();
	if (GameEngine::handler.keyDown(irr::KEY_KEY_W))
	{

			pos += movedir * timeDiff * MoveSpeed;
			btVector3 b = GameEngine::Physics::irrVec3ToBtVec3(movedir * timeDiff * MoveSpeed);
			_playerRB->applyCentralImpulse(GameEngine::Physics::irrVec3ToBtVec3(movedir * timeDiff * MoveSpeed));
	}
	if (GameEngine::handler.keyDown(irr::KEY_KEY_S))
	{
			pos -= movedir * timeDiff * MoveSpeed;
			btVector3 b = GameEngine::Physics::irrVec3ToBtVec3(movedir * timeDiff * MoveSpeed);
			_playerRB->applyCentralImpulse(GameEngine::Physics::irrVec3ToBtVec3(-movedir * timeDiff * MoveSpeed));
	}
	// strafing

	irr::core::vector3df strafevect = target;
	//strafevect = strafevect.crossProduct( camera->getUpVector());
	strafevect = strafevect.crossProduct(GameEngine::Physics::btVecToirrVec3(_physicsMesh->getRB()->getWorldTransform().getBasis()[1].normalize()));

	if (NoVerticalMovement)
			strafevect.Y = 0.0f;

	strafevect.normalize();

	if (GameEngine::handler.keyDown(irr::KEY_KEY_A))
	{
	//      pos += strafevect * timeDiff * MoveSpeed;
	//      body->setPosition(pos);
			_playerRB->applyCentralImpulse(GameEngine::Physics::irrVec3ToBtVec3(strafevect * timeDiff * MoveSpeed));
	}
	if (GameEngine::handler.keyDown(irr::KEY_KEY_D))
	{
			//pos -= strafevect * timeDiff * MoveSpeed;
			//body->setPosition(pos);
			_playerRB->applyCentralImpulse(GameEngine::Physics::irrVec3ToBtVec3(-(strafevect * timeDiff * MoveSpeed)));
	}

	// write translation
        
        
	//body->setPosition(pos);
	//body->setRotation(relativeRotation);
	//camera->setPosition(pos);
        
	// write right target
	//target += pos;
	//camera->setTarget(target);

        
	//target += pos;
	//camera->setTarget(target);
}

void Player::update4(float delta)
{	
	if(!_ghostObject ){
		return;
	}
	/*
	//during idle mode, just run 1 simulation step maximum
	int maxSimSubSteps = m_idle ? 1 : 2;
	if (m_idle)
		dt = 1.0/420.f;
	*/

	///set walkDirection for our character
	btTransform xform;
	xform = _ghostObject->getWorldTransform ();

	btVector3 forwardDir = xform.getBasis()[2];
	//	printf("forwardDir=%f,%f,%f\n",forwardDir[0],forwardDir[1],forwardDir[2]);
	btVector3 upDir = xform.getBasis()[1];
	btVector3 strafeDir = xform.getBasis()[0];
	forwardDir.normalize ();
	upDir.normalize ();
	strafeDir.normalize ();

	btVector3 walkDirection = btVector3(0.0, 0.0, 0.0);
	btScalar walkVelocity = btScalar(1.1) * 100.0;
	btScalar walkSpeed = walkVelocity * delta;

	//rotate view
	if (GameEngine::handler.keyDown(irr::KEY_KEY_A))
	{
		btMatrix3x3 orn = _ghostObject->getWorldTransform().getBasis();
		orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),5.0f*delta));
		_ghostObject->getWorldTransform ().setBasis(orn);
	}

	if (GameEngine::handler.keyDown(irr::KEY_KEY_D))
	{
		btMatrix3x3 orn = _ghostObject->getWorldTransform().getBasis();
		orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),-5.0f*delta));
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
	btVector3 gg = walkDirection*walkSpeed;
	//if(_characterC && gg.length() != btScalar(0)){
		_characterC->setWalkDirection(gg);
//	}
	std::cout <<std::endl;
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
