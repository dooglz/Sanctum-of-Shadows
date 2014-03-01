#include "Player.h"



void Player::intitalise(irr::core::vector3df position)
{
	_physicsMesh = new Box(GameEngine::Physics::irrVec3ToBtVec3(position),irr::core::vector3df(60.0f,100.0f,60.0f),60.0f);
	_camera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNode(_physicsMesh->getNode(),irr::core::vector3df(0,0,0));
	_camera->bindTargetAndRotation(true);

	//

	btTransform startTransform;
	startTransform.setIdentity ();
	//startTransform.setOrigin (btVector3(0.0, 4.0, 0.0));
	startTransform.setOrigin (GameEngine::Physics::irrVec3ToBtVec3(position));


	m_ghostObject = new btPairCachingGhostObject();
	m_ghostObject->setWorldTransform(startTransform);

	btScalar characterHeight=1.75;
	btScalar characterWidth =1.75;
	btConvexShape* capsule = new btCapsuleShape(characterWidth,characterHeight);
	m_ghostObject->setCollisionShape (capsule);
	m_ghostObject->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);

	btScalar stepHeight = btScalar(0.35);
	m_character = new btKinematicCharacterController (m_ghostObject,capsule,stepHeight);
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