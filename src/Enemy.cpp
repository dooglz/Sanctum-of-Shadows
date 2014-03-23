#include "Enemy.h"
#include "Message.h"
#include "MessageHandler.h"
#include "SanctumOfShadows.h"
Player* Enemy::_player;

Enemy::Enemy(irr::core::vector3df position): Character(-1,0,"Skeletors")
{
	_walkVelocity = btScalar(200);
	irr::core::vector3df enemyScale = irr::core::vector3df(50.0f,80.0f,50.0f);
	//Physics Kinematic caracter Object
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
	//int n1 = rand() % 100;
	//int n2 = rand() % 250;
	//int n3 = rand() % 100;
	walkleft = false;
	walkright = false;
	walkforward = false;
	walkback = false;
	Character::update(delta);

	//get dotProduct of the look vector and player position vector
	float angleToplayer =  _forwardDir.angle(GameEngine::Physics::irrVec3ToBtVec3 ((_player->getNode()->getPosition() - _node->getPosition())));
	//clamp
	if(angleToplayer > 1)
	{
		angleToplayer =1;
	}
	else if(angleToplayer < -1)
	{
		angleToplayer = -1;
	}
	//cos^-1 to get angle
	angleToplayer = acos(angleToplayer);

	//get The Y component of the croosproduct between the look vector and player position vector
	float crossToplayer = _forwardDir.cross(GameEngine::Physics::irrVec3ToBtVec3 ((_player->getNode()->getPosition() - _node->getPosition()))).getY(); 
	
	//TODO put these in a header, with other things when enemies get more complicated
	float visibleRange = 300.0f;
	float combatRange = 130.0f;

	float distanceToPlayer = (_player->getNode()->getPosition() - _node->getPosition()).getLength();
	if(distanceToPlayer < visibleRange )
	{
		if(crossToplayer < -0.15f)
		{
			walkleft=true;
		}
		else if(crossToplayer > 0.15f)
		{
			walkright = true;
		}

		if(distanceToPlayer > combatRange)
		{
			//move towards player, if he is infront of us
			if(angleToplayer < 60)
			{
				walkforward = true;
			}
		}
		else
		{
			//We are in attack range
			if(distanceToPlayer < (0.8f*combatRange))
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
	if (SanctumOfShadows::player->isAlive() && (SanctumOfShadows::player->getNode()->getPosition() - _node->getPosition()).getLength() < combatRange)
	{
		//create a message 
		GameEngine::Message message(SanctumOfShadows::player,"playerHealthDecrease",0);
		//send it via the message handler
		GameEngine::MessageHandler::sendMessage(message);
	}					
			
	if(_health <= 0)
	{
		std::cerr << "Enemy is dead" << std::endl;
		die();
	}

}


bool Enemy::loadContent()
{
	return true;
}

void Enemy::unloadContent()
{
	Character::unloadContent();
}


void Enemy::handleMessage(const GameEngine::Message& message)
{
	if (message.message == "healthDecrease")
	{
		//recieved message to take damamge
		_health = _health - 20.0f;
		_characterC->setMaxJumpHeight(20);
		_characterC->setFallSpeed(200);
		_characterC->setJumpSpeed(20);
		_characterC->jump();


	}
}