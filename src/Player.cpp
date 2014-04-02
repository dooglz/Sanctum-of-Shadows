
#include "Player.h"

// The Maximum radius of the lanterns effects.
const float Player::_Lanternmaxradius = 0.45f;
const float Player::_Lanternrminradius = 0.06f;

Player::Player(GameEngine::Scene* parentScene, irr::core::vector3df position): Character(parentScene,0,"player")
{
	_fuelLevel = 1.0f;
	_LanternOn = true;

	_walkVelocity = btScalar(6);
	_rotateSpeed = 5.0f;

	irr::core::vector3df playerScale = irr::core::vector3df(60.0f,100.0f,60.0f);
	
	//Physics Kinematic character Object
	_characterC = addCharacter((btScalar)1.0f, &btVector3(position.X, position.Y, position.Z), (btScalar)50, (btScalar)30);
	
	//player render node
	//_node = GameEngine::engine.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_node = GameEngine::engine.getDevice()->getSceneManager()->addEmptySceneNode();
	//_node->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_stone.png"));
	_node->setScale(playerScale);

	//The player doesn't need lighting
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	//player camera
	_camera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNode(_node,irr::core::vector3df(0,0,0));
	_camera->bindTargetAndRotation(true);
	_health = 100.0f;
	_Lanternlight = GameEngine::engine.getDevice()->getSceneManager()->addLightSceneNode(
		_node, irr::core::vector3df(0,0.0f,0),			//Parent and offset
		irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f),	//Colour
		450.0f//Radius
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
			_fuelLevel -= 0.02f*delta;
			float light = _Lanternrminradius + (_fuelLevel * (_Lanternmaxradius - _Lanternrminradius));

			irr::video::SLight& data = 	_Lanternlight->getLightData();
			data.DiffuseColor = (irr::video::SColorf(light, light, light, 1.0f));
			_Lanternlight->setLightData(data);

			//_Lanternlight->setRadius(_Lanternrminradius);
			irr::core::stringw str = "Lantern fuel: ";
			str += _fuelLevel;
			GameEngine::UI::displayTextMessage(str,0);
			str = "Lantern strength: ";
			str += light;
			GameEngine::UI::displayTextMessage(str,0);
			}
		else
		{
			//toggleLantern(false);
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
		std::list<Entity*>* entities = _parentScene->getEntityManager()->getNamedEntity("Skeletors");
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
		//_Lanternlight->setVisible(true);
		_LanternOn = true;
	}
	else
	{
		irr::video::SLight& data = 	_Lanternlight->getLightData();
			data.DiffuseColor = (irr::video::SColorf(_Lanternrminradius, _Lanternrminradius, _Lanternrminradius, 1.0f));
			_Lanternlight->setLightData(data);
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
			//take damage off of players health
		//	_health = _health - 10.0f;
		}
		delete message.data;
	}
}

Player::~Player()
{
	if(_Lanternlight != nullptr )
	{
		_Lanternlight->remove();
		_Lanternlight = NULL;
	}
	if(_camera != nullptr )
	{
		_camera->remove();
		_camera = NULL;
	}
}