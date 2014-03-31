#include "cheapCharacter.h"


cheapCharacter::cheapCharacter(GameEngine::Scene* parentScene, irr::scene::ISceneNode* node,const std::string& name):Entity(parentScene,node,name){}

//! Creates the controller and adds a blank scene node.
void cheapCharacter::intitalise(irr::core::vector3df position, irr::core::vector3df size)
{
	_position = position;
	_walkVelocity = btScalar(6);
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
	float walkSpeed = _walkVelocity;
		
	//rotate (needs delta as it transforms directly)
	if (walkleft == true)
	{
		_node->setRotation(_node->getRotation() + (irr::core::vector3df(0,-1,0) * _rotateSpeed * delta) );
		//btMatrix3x3 orn = _ghostObject->getWorldTransform().getBasis();
		//orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),-1.0f * _rotateSpeed * delta));
	//	_ghostObject->getWorldTransform ().setBasis(orn);
	}

	if (walkright == true)
	{
		_node->setRotation(_node->getRotation() + (irr::core::vector3df(0,1,0) * _rotateSpeed * delta) );
		//btMatrix3x3 orn = _ghostObject->getWorldTransform().getBasis();
	//	orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0), _rotateSpeed * delta));
		//_ghostObject->getWorldTransform ().setBasis(orn);
	}

	if (walkforward == true)
	{
		walkDirection += _forwardDir;
	}

	if (walkback == true)
	{
		walkDirection -= _forwardDir;	
	}

	walkDirection *= (_walkVelocity * delta);

	//_characterC->setWalkDirection(walkDirection*walkSpeed);

	//Set the render node's position and rotation to match _ghostObject's
	//btMotionState is currently only available for rigid bodies and not Ghost Objects
	if(_node)
	{
		//who knows if thios works
		//_node->getAbsoluteTransformation().transformVect(walkDirection);
		_node->setPosition(_node->getPosition() + walkDirection);
		_position = _node->getPosition();

	//	worldTrans = _ghostObject->getWorldTransform();
		//worldTrans.getOpenGLMatrix(matr.pointer());
	//	_node->setRotation(matr.getRotationDegrees());
	//	_node->setPosition(matr.getTranslation());
	//	_position = matr.getTranslation();
	}
}

cheapCharacter::~cheapCharacter()
{

}