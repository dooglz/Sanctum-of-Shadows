#include "Enemy.h"
#include "Message.h"
#include "MessageHandler.h"
#include "SanctumOfShadows.h"
#include "irrKlang.h"
#include <iostream>
#pragma comment(lib, "irrKlang.lib")

Player* Enemy::_player;

Enemy::Enemy(GameEngine::Scene* parentScene, irr::core::vector3df position): Character(parentScene,0,"Skeletors")
{
	_walkVelocity = btScalar(4.5);
	_rotateSpeed = 5.0f;

	irr::core::vector3df enemyScale = irr::core::vector3df(50.0f,80.0f,50.0f);
	//Physics Kinematic character Object
	_characterC = addCharacter((btScalar)1.0f, &btVector3(position.X, position.Y, position.Z), (btScalar)enemyScale.Y/2, (btScalar)enemyScale.X/2);
	//Render node
	_node = GameEngine::engine.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_node->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_flurry.jpg"));
	_node->setScale(enemyScale);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	_node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	_health = 80.0f;
	_visibleRange = 300.0f;
	_combatRange = 130.0f;
	_state = IDLE;
	_targetPosition = position;
	walk(0);
}


void Enemy::update(float delta)
{	

	//int n2 = rand() % 250;
	//int n3 = rand() % 100;
	walkleft = false;
	walkright = false;
	walkforward = false;
	walkback = false;
	Character::update(delta);

	//HAAX! We discard the Y(up down) component for steering calculation, as enemies can't fly.
	irr::core::vector2df currentPosition = irr::core::vector2df(_position.X,_position.Z);
	irr::core::vector2df playerPosition = irr::core::vector2df(_player->getNode()->getPosition().X,_player->getNode()->getPosition().Z);
	irr::core::vector2df targetPosition = irr::core::vector2df(_targetPosition.X,_targetPosition.Z);
	
	float distanceToPlayer = (playerPosition - currentPosition).getLength();

	//Is the player in our aggro bubble?
	if(_player->isAlive() && distanceToPlayer < _visibleRange)
	{
		//YES.
		_state = COMBAT;
		_targetPosition = _player->getNode()->getPosition();
		targetPosition = irr::core::vector2df(_targetPosition.X,_targetPosition.Z);
	}
	else
	{
		//NO
		_state = IDLE;
	}

	switch (_state) {
		case COMBAT:
			process_combat(delta);
			break;
		case IDLE:

			break;
	}

	//get dotProduct of the look vector and player position vector
	float angleToTarget =  _forwardDir.angle(GameEngine::Physics::irrVec3ToBtVec3 ((_targetPosition - _node->getPosition())));

	//clamp
	//angleToTarget =  angleToTarget < -1.0f ? -1.0f : (angleToTarget > 1.0f ? 1.0f : angleToTarget);
	if(angleToTarget > 1)
	{
		angleToTarget =1;
	}
	else if(angleToTarget < -1)
	{
		angleToTarget = -1;
	}


	//cos^-1 to get angle
	angleToTarget = acos(angleToTarget);

	//get The Y component of the crossproduct between the look vector and player position vector
	float crossToTarget = _forwardDir.cross(GameEngine::Physics::irrVec3ToBtVec3 ((_targetPosition - _node->getPosition()))).getY(); 

	float distanceToTarget = (_targetPosition - _node->getPosition()).getLength();

	if(crossToTarget < -10.5f)
	{
		walkleft=true;
	}
	else if(crossToTarget > 10.5f)
	{
		walkright = true;
	}
	if(angleToTarget < 60)
	{
		walkforward = true;
	}

	walk(delta);

	
	if(_health <= 0)
	{
		std::cerr << "Enemy is dead" << std::endl;

		//play the sound for when enemy dies
		GameEngine::Engine::soundengine->play2D("sounds/enemydead.mp3", false);
		die();
	}

}

void Enemy::process_combat(float delta)
{
	//a random number for enemy combat statistic to hit player
	int n1 = rand() % 400;
	float distanceToPlayer = (_player->getNode()->getPosition()  - _node->getPosition()).getLength();

	//are we within combat radius?
	if(distanceToPlayer < _combatRange)
	{
		//yes, but are we too close?
		if(distanceToPlayer < (0.8f*_combatRange))
		{
			//move away from player as we are too close
			walkback = true;
		}
		else
		{
			//roll dice, damage player
			if( n1 < 3)
			{	
				GameEngine::Message message(_player,"playerHealthDecrease",0);
				GameEngine::MessageHandler::sendMessage(message);
			}
		}
	}
	else
	{
		//Not in combat radius, move closer
	}
		
}


void Enemy::handleMessage(const GameEngine::Message& message)
{
	if (message.message == "healthDecrease")
	{
		//received message to take damage
		_health = _health - 20.0f;
		//"bob" the enemy to notify damage taken
		_characterC->setMaxJumpHeight(30);
		_characterC->setGravity(100);
		_characterC->setJumpSpeed(20);
		_characterC->jump();
		//play sound for when the enemy takes damage
		GameEngine::Engine::soundengine->play2D("sounds/hit.wav", false);
	}

}

void Enemy::setPlayer(Player* player){
	_player = player;
}