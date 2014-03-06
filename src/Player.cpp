#include "Player.h"

void Player::intitalise(irr::core::vector3df position)
{
	irr::core::vector3df playerScale = irr::core::vector3df(60.0f,100.0f,60.0f);
	//Physics Kinematic caracter Object
	_characterC = addCharacter((btScalar)1.0f, &btVector3(position.X, position.Y, position.Z), (btScalar)50, (btScalar)30);
	//player render node
	//_playerNode = GameEngine::engine.getDevice()->getSceneManager()->addEmptySceneNode();
	_node = GameEngine::engine.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_node->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_stone.png"));
	_node->setScale(playerScale);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	//player camera
	_camera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNode(_node,irr::core::vector3df(0,0,0));
	_camera->bindTargetAndRotation(true);
}

void Player::update(float delta)
{	
	walkleft = false;
	walkright = false;
	walkforward = false;
	walkback = false;

	if (GameEngine::handler.keyDown(irr::KEY_KEY_A))
	{
		walkleft = true;
	}

	if (GameEngine::handler.keyDown(irr::KEY_KEY_D))
	{
		walkright = true;
	}

	if (GameEngine::handler.keyDown(irr::KEY_KEY_W))
	{
		walkforward = true;
	}

	if (GameEngine::handler.keyDown(irr::KEY_KEY_S))
	{
		walkleft = true;
	}
	walk(delta);
}

bool Player::loadContent()
{
	return true;
}

void Player::unloadContent()
{

}