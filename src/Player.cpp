#include "Player.h"

#include "SanctumOfShadows.h"
Player::Player(irr::core::vector3df position): Character(-1,0,"player")
{
	fuelLevel = 1.0f;
	_Lanternradius= 300.0f;
	LanternOn = true;

	_walkVelocity = btScalar(1000);
	irr::core::vector3df playerScale = irr::core::vector3df(60.0f,100.0f,60.0f);
	//Physics Kinematic caracter Object
	_characterC = addCharacter((btScalar)1.0f, &btVector3(position.X, position.Y, position.Z), (btScalar)50, (btScalar)30);
	//player render node
	//_node = GameEngine::engine.getDevice()->getSceneManager()->addEmptySceneNode();
	_node = GameEngine::engine.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_node->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_stone.png"));
	_node->setScale(playerScale);
	//The player doesn't need lighting
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	//_node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	//player camera
	_camera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNode(_node,irr::core::vector3df(0,0,0));
	_camera->bindTargetAndRotation(true);
	_health = 100.0f;
	_Lanternlight = GameEngine::engine.getDevice()->getSceneManager()->addLightSceneNode(
		_node, irr::core::vector3df(0,1.0f,0),			//Parent and offset
		irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f),	//Colour
		(irr::f32)_Lanternradius//Radius
	);

}

void Player::update(float delta)
{	
	if(_health <= 0.0f)
	{
		handleDeath();
		return;
	}

	float combatRange = 130.0f;
	walkleft = false;
	walkright = false;
	walkforward = false;
	walkback = false;
	Character::update(delta);


	if(LanternOn && fuelLevel > 0 )
	{
		    fuelLevel -= 0.01*delta;
			irr::core::stringw str = "Lantern fuel: ";
			str += fuelLevel * _Lanternradius;
			GameEngine::UI::displayTextMessage(str,0);
			Player::setRadius(fuelLevel * _Lanternradius);
	}

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
		walkback = true;
	}
	walk(delta);

	if(_camera)
	{
		_camera->setTarget( _node->getPosition()+GameEngine::Physics::btVecToirrVec3(_forwardDir) );
	}

	if(GameEngine::handler.keyFired(irr::KEY_KEY_Q))
	{
		Player::fuel(delta);
	}
	
	if  (GameEngine::handler.keyFired(irr::KEY_SPACE))
	{
		std::list<Entity*>* entities = GameEngine::EntityManager::getNamedEntity("Skeletors");
		//if the list isn't empty, then we check if we have hit something 
		if(entities->size() > 0)
		{
			for(auto iter = entities->begin(); iter != entities->end(); ++iter)
			{
				//check if the current Skeletor is alive. no point checking collision if it isn't 
				if ((*iter)->isAlive() && ((*iter)->getNode()->getPosition() - _node->getPosition()).getLength() < combatRange)
				{
					//create a message 
					GameEngine::Message message((*iter),"healthDecrease",0);
					//send it via the message handler
					GameEngine::MessageHandler::sendMessage(message);
				}					
			}
		}
	}

}

bool Player::loadContent()
{
	return true;
}

void Player::unloadContent()
{
	if(_camera)
	{
		_camera->drop();
		_camera = 0;
	}
	Character::unloadContent();
}


void Player::handleMessage(const GameEngine::Message& message)
{
	//handle incoming message
	if(message.message == "playerHealthDecrease")
	{
		if(_health >= 0)
		{
			_health = _health - 0.05f;
		}
		delete message.data;
	}
}




void Player::fuel(float delta)
{
		if(LanternOn)
		{
			//Player::setRadius(0);
			_Lanternlight->setVisible(false);
			LanternOn = false;
		}
		else 
		{
			_Lanternlight->setVisible(true);
			LanternOn = true;
		}
}

void Player::handleDeath()
{
	_alive = false;
	SanctumOfShadows::GameOver();
}
