#include "cheapCharacter.h"


cheapCharacter::cheapCharacter(GameEngine::Scene* parentScene,const std::string& name):Character(parentScene,name){}

//! Creates the controller and adds a blank scene node.
void cheapCharacter::intitalise(irr::core::vector3df position, irr::core::vector3df size)
{
	_position = position;
	_walkSpeed = 6.0f;
	_rotateSpeed = 5.0f;

	if(size.getLengthSQ() == 0)
	{
		size = irr::core::vector3df(50.0f,80.0f,50.0f);
	}

	//render node
	_node = GameEngine::engine.getDevice()->getSceneManager()->addEmptySceneNode();
}

//! Recalculate position transforms and direction vectors, call this before Walk.
void cheapCharacter::update(float delta)
{
	_xform =_node->getRelativeTransformation();

	_forwardDir = irr::core::vector3df(_xform[8],_xform[9],_xform[10]); 
    _forwardDir.normalize();

	_upDir = irr::core::vector3df(_xform[4],_xform[5],_xform[6]); 
	_upDir.normalize();

	_strafeDir = irr::core::vector3df(_xform[0],_xform[1],_xform[2]); 
	_strafeDir.normalize ();
}

//! Move based on the walk flags.
void cheapCharacter::walk(float delta)
{	
	irr::core::vector3df walkDirection = irr::core::vector3df(0.0f, 0.0f, 0.0f);
		
	//rotate (needs delta as it transforms directly)
	if (walkleft)
	{
		_node->setRotation(_node->getRotation() + (irr::core::vector3df(0,-1,0) * _rotateSpeed * delta) );
	}
	else if (walkright)
	{
		_node->setRotation(_node->getRotation() + (irr::core::vector3df(0,1,0) * _rotateSpeed * delta) );
	}

	//Forward / BAckwards movement
	if (walkforward)
	{
		walkDirection += _forwardDir;
	}

	if (walkback)
	{
		walkDirection -= _forwardDir;	
	}

	//Multiply the normalised direction vector by Speed and delta.
	walkDirection *= (_walkSpeed * delta);

	//Move the node
	if(_node)
	{
		_node->setPosition(_node->getPosition() + walkDirection);
		_position = _node->getPosition();
	}
}

cheapCharacter::~cheapCharacter()
{

}