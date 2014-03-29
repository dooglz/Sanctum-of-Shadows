#include "Enemy.h"
#include "Message.h"
#include "MessageHandler.h"
#include "SanctumOfShadows.h"
#include "irrKlang.h"
#include <iostream>
#pragma comment(lib, "irrKlang.lib")

Player* Enemy::_player;

Enemy::Enemy(GameEngine::GameState* parentState, irr::core::vector3df position): Character(parentState,0,"Skeletors")
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
}


void Enemy::update(float delta)
{	
	//a random number for enemy combat statistic to hit player
	int n1 = rand() % 400;
	//int n2 = rand() % 250;
	//int n3 = rand() % 100;
	walkleft = false;
	walkright = false;
	walkforward = false;
	walkback = false;
	Character::update(delta);
	
	//get dotProduct of the look vector and player position vector
	float angleToTarget =  _forwardDir.angle(GameEngine::Physics::irrVec3ToBtVec3 ((targetPosition - _node->getPosition())));
	//clamp
	
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
	float crossToTarget = _forwardDir.cross(GameEngine::Physics::irrVec3ToBtVec3 ((targetPosition - _node->getPosition()))).getY(); 
	
	//TODO put these in a header, with other things when enemies get more complicated
	float visibleRange = 300.0f;
	float combatRange = 130.0f;
	float distanceToTarget= (targetPosition - _node->getPosition()).getLength();

	if((_player->getNode()->getPosition() - _node->getPosition()).getLength() < visibleRange)
	{
		targetPosition = _player->getNode()->getPosition();
	}

	if(distanceToTarget < visibleRange )
	{
		if(crossToTarget < -10.5f)
		{
			walkleft=true;
		}
		else if(crossToTarget > 10.5f)
		{
			walkright = true;
		}

		if(distanceToTarget > combatRange)
		{
			//move towards player, if he is in front of us
			if(angleToTarget < 60)
			{
				walkforward = true;
			}
		}
		else
		{
			//We are in attack range
			if(distanceToTarget < (0.8f*combatRange))
			{
				//move away from player as we are too close
				walkback = true;
			}
			else
			{
				//TODO attack();
			}
		}
	}
	walk(delta);

	//damage player
	if (_player->isAlive() && (_player->getNode()->getPosition() - _node->getPosition()).getLength() < combatRange)
	{
		if( n1 < 3)
		{
		//create a message 
		GameEngine::Message message(_player,"playerHealthDecrease",0);
		//send it via the message handler
		GameEngine::MessageHandler::sendMessage(message);
		}
	}					
			
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