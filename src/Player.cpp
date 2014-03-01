#include "Player.h"

void Player::intitalise(irr::core::vector3df position)
{
	_physicsMesh = new Box(GameEngine::Physics::irrVec3ToBtVec3(position),irr::core::vector3df(60.0f,100.0f,60.0f),60.0f);
	_camera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNode(_physicsMesh->getNode(),irr::core::vector3df(0,0,0));
	_camera->bindTargetAndRotation(true);
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
<<<<<<< HEAD
	_physicsMesh->getRB()->applyForce( btVector3(100 , 0 ,0 ), btVector3(0 , 0 ,0 ));
=======
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
>>>>>>> 92a0e0242dfde6437f4b2920d359974b3bd909e0
}


