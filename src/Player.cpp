
#include "Player.h"

// The Maximum radius of the lanterns effects.
const float Player::_Lanternmaxradius = 300.0f;

Player::Player(GameEngine::GameState* parentState, irr::core::vector3df position): Character(parentState,0,"player")
{
	_fuelLevel = 1.0f;
	_LanternOn = true;

	_walkVelocity = btScalar(6);
	_rotateSpeed = 5.0f;

	irr::core::vector3df playerScale = irr::core::vector3df(60.0f,100.0f,60.0f);
	
	//Physics Kinematic character Object
	_characterC = addCharacter((btScalar)1.0f, &btVector3(position.X, position.Y, position.Z), (btScalar)50, (btScalar)30);
	
	//player render node
	_node = GameEngine::engine.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_node->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_stone.png"));
	_node->setScale(playerScale);

	//The player doesn't need lighting
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	//player camera
	_camera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNode(_node,irr::core::vector3df(0,0,0));
	_camera->bindTargetAndRotation(true);
	_health = 100.0f;
	_Lanternlight = GameEngine::engine.getDevice()->getSceneManager()->addLightSceneNode(
		_node, irr::core::vector3df(0,1.0f,0),			//Parent and offset
		irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f),	//Colour
		(irr::f32)_Lanternmaxradius//Radius
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


	if(_LanternOn)
	{
		 if (_fuelLevel > 0){ 
		    _fuelLevel -= 0.01f*delta;
			irr::core::stringw str = "Lantern fuel: ";
			str += _Lanternlight->getRadius();
			GameEngine::UI::displayTextMessage(str,0);
			_Lanternlight->setRadius(_fuelLevel * _Lanternmaxradius);
		 }
		 else
		 {
			 toggleLantern(false);
		 }
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
		Player::toggleLantern(!_LanternOn);
	}
	
	if  (GameEngine::handler.keyFired(irr::KEY_SPACE))
	{
		std::list<Entity*>* entities = _parentstate->getEntityManager()->getNamedEntity("Skeletors");
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

//! Set the state of the lantern, will not light if no fuel.
void Player::toggleLantern(bool onoff)
{
	if(onoff && _fuelLevel > 0)
	{
		_Lanternlight->setVisible(true);
		_LanternOn = true;
	}
	else
	{
		_Lanternlight->setVisible(false);
		_LanternOn = false;
	}
}

//! called when health <= 0
void Player::handleDeath()
{
	_alive = false;
	//SanctumOfShadows::GameOver();
}

void Player::handleMessage(const GameEngine::Message& message)
{
	//handle incoming message
	if(message.message == "playerHealthDecrease")
	{
		if(_health >= 0)
		{
			//play sound for enemy taking damage
			GameEngine::Engine::soundengine->play2D("sounds/damage.wav", false);
			
			//"bob" the player to notify damage taken
			_characterC->setMaxJumpHeight(20);
			_characterC->setJumpSpeed(20);
			_characterC->setGravity(100);
			_characterC->jump();

			_health = _health - 10.0f;
		}
		delete message.data;
	}
}

Player::~Player()
{
	if(_camera != nullptr )
	{
		_camera->drop();
		_camera = NULL;
	}
}