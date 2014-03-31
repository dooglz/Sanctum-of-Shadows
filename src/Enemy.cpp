#include "Enemy.h"
#include "Message.h"
#include "MessageHandler.h"
#include "SanctumOfShadows.h"
#include "irrKlang.h"
#include <iostream>
#include "Pathfinder.h"
#pragma comment(lib, "irrKlang.lib")

Player* Enemy::_player;

Enemy::Enemy(GameEngine::Scene* parentScene, irr::core::vector3df position): Character(parentScene,0,"Skeletors")
{
	irr::core::vector3df enemyScale = irr::core::vector3df(50.0f,80.0f,50.0f);
	//Physics Kinematic character Object
	_characterC = addCharacter((btScalar)1.0f, &btVector3(position.X, position.Y, position.Z), (btScalar)enemyScale.Y/2, (btScalar)enemyScale.X/2);
	_characterC->setMaxJumpHeight(30);
	_characterC->setGravity(100);
	_characterC->setJumpSpeed(20);
	//Render node
	_node = GameEngine::engine.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_node->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_flurry.jpg"));
	_node->setScale(enemyScale);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	//
	_walkVelocity = btScalar(4.5);
	_rotateSpeed = 5.0f;
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

	float distanceToPlayer = (_player->getNode()->getPosition()  - _position).getLength();

	//Is the player in our aggro bubble?
	if(_player->isAlive() && distanceToPlayer < _visibleRange)
	{
		//YES.
		_state = COMBAT;
		_targetPosition = _player->getNode()->getPosition();
	}
	else
	{
		//NO
		_state = IDLE;
	}

	irr::core::vector3df vector3ToTarget = (_targetPosition - _position);

	float distanceToTarget = vector3ToTarget.getLength();
	float flatdistanceToTarget = irr::core::vector3df(vector3ToTarget.X,0,vector3ToTarget.Z).getLength();

	//get dotProduct of the look vector and player position vector
	float dotToTarget =  _forwardDir.dot(GameEngine::Physics::irrVec3ToBtVec3 (vector3ToTarget));

	//normalize dot (assume _forwardDir is normalised)
	float angleToTarget = dotToTarget / distanceToTarget;

	//clamp to avoid rounding errors.
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

	//Crossproduct between the look vector and player position vector
	btVector3 crossToTarget = _forwardDir.cross(GameEngine::Physics::irrVec3ToBtVec3 (vector3ToTarget)); 

	if(crossToTarget.getY() < -10.5f)
	{
		//right
		walkleft=true;
	}
	else if(crossToTarget.getY() > 10.5f)
	{
		//left
		walkright = true;
	}
	else
	{
		//Target is either directly in front or behind.
		if(dotToTarget < 0)
		{
			//Target is Directly Behind, causing character to stall. Nudge to the left to start moving again
			walkleft=true;
		}
	}

	if(flatdistanceToTarget >= (_combatRange)) 
	{
		if(dotToTarget > 0)
		{
			//in front		
			if(angleToTarget < 35.0f){
				//target is within view radius
				walkforward = true;
			}
		}
	}
	else
	{
		if(_state == COMBAT)
		{
			//We have reached the player.
			if(flatdistanceToTarget < (0.8f*_combatRange)) 
			{
				//move away from player as we are too close
				walkback = true;
			}
			else
			{
				//roll dice, damage player
				if((rand() % 400) < 3)
				{	
					GameEngine::Message message(_player,"playerHealthDecrease",0);
					GameEngine::MessageHandler::sendMessage(message);
				}
			}
		}
		else if(_state == IDLE)
		{
			//We are at our target, find a new one.
			//std::cout << "Location reached" << std::endl;
			//_targetPosition = Pathfinder::getResolvedLocation(Pathfinder::getDarkLocation());
			_targetPosition = Pathfinder::getResolvedLocation(
					Pathfinder::getAdjacentDarkLocation(
						Pathfinder::getResolvedCoord(_position)
					)
				);
		}

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


void Enemy::handleMessage(const GameEngine::Message& message)
{
	if (message.message == "healthDecrease")
	{
		//received message to take damage
		_health = _health - 20.0f;
		//"bob" the enemy to notify damage taken
		_characterC->jump();
		//play sound for when the enemy takes damage
		GameEngine::Engine::soundengine->play2D("sounds/hit.wav", false);
	}

}

void Enemy::setPlayer(Player* player){
	_player = player;
}
