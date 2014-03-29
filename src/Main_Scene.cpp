#pragma once
#include "Main_Scene.h"
#include <iostream>
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
#include "Box.h"

irr::scene::ICameraSceneNode* Flycamera;
irr::scene::ICameraSceneNode* Menucamera;
irr::scene::ILightSceneNode* workLight;
irr::scene::ILightSceneNode* spinningLight;

bool Main_Scene::_gameover;
bool Main_Scene::_gamewon;

Player* Main_Scene::player;
Enemy* enemy;
Level* level;
irr::gui::IGUIInOutFader* fader;

Main_Scene::Main_Scene():GameState("main")
{
	std::cout << "Main_Scene constructor" << std::endl;
}

// Destructor
Main_Scene::~Main_Scene()
{
	std::cout << "Main_Scene destructor" << std::endl;
	flush();
}

bool Main_Scene::loadContent()
{
	std::cout << "Main_Scene loadContent" << std::endl;
	return true;
}

void Main_Scene::initialize()
{
	flush();

	std::cout << "Main_Scene initialize" << std::endl;
	

	irr::scene::ISceneManager* smgr = GameEngine::engine.getDevice()->getSceneManager();

	//Cameras
	Flycamera = smgr->addCameraSceneNodeFPS();
	Flycamera->setPosition(irr::core::vector3df(0,100,0));
	Flycamera->setFarValue(10000.0f);
	
	Menucamera = smgr->addCameraSceneNode(0,irr::core::vector3df(0,100,223),irr::core::vector3df(0,100,0));

				
	//Lights
	workLight = smgr->addLightSceneNode(0, irr::core::vector3df(0,200.0f,0), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 1000.0f);
	// create spinning light
	spinningLight = smgr->addLightSceneNode(0, irr::core::vector3df(0,300.0f,0), irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 1000.0f);
	irr::scene::ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator (irr::core::vector3df(0,50,0),300.0f);
	spinningLight->addAnimator(anim);
	anim->drop();

	irr::scene::ISceneNode* LightSpriteNode = smgr->addBillboardSceneNode(spinningLight, irr::core::dimension2d<irr::f32>(50, 50));
	LightSpriteNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	LightSpriteNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	LightSpriteNode->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/particlewhite.bmp"));

	//fader
	fader = GameEngine::engine.getDevice()->getGUIEnvironment()->addInOutFader();
    fader->setColor(irr::video::SColor(0,0,0,0));

	
	//load the level
	level = new Level(this);
	level->loadContent();
	level->intitalise();
	

	//Game Entities
	player = new Player(this,irr::core::vector3df(0,200.0f,0));
	Enemy::setPlayer(player);
	enemy = new Enemy(this,irr::core::vector3df(400.0f,200.0f,0));
	//

	irr::core::stringw str = "Game Initialised";
	GameEngine::UI::displayTextMessage(str,2000);

	reset();

}

void Main_Scene::flush()
{
	std::cout << "Main_Scene Flush" << std::endl;

	if (Menucamera != nullptr )
	{
		Menucamera->remove();
		Menucamera = NULL;
	}

	if (workLight != nullptr )
	{
		workLight->remove();
		workLight = NULL;
	}

	if (spinningLight != nullptr )
	{
		spinningLight->remove();
		spinningLight = NULL;
	}

	if (Menucamera != nullptr )
	{
		Flycamera->remove();
		Flycamera = NULL;
	}
	
	if(player != nullptr )
	{
		delete player;
		player = NULL;
	}
	
	if(enemy != nullptr )
	{
		delete enemy;
		enemy = NULL;
	}

	if(level != nullptr )
	{
		delete level;
		level = NULL;
	}
	
	if(fader != nullptr )
	{
		//fader->drop();
		fader->remove();
		fader = NULL;
	}
}

// Run per-frame game logic.
void Main_Scene::update(float delta)
{
	
	//display player health
	irr::core::stringw str = "Player Health: ";
	str += player->getHealth();
	GameEngine::UI::displayTextMessage(str,0);


	if(level->isGameWon() == true)
	{
		GameWon();
	}


	//Debug Camera commands
	if(GameEngine::handler.keyFired(irr::KEY_F1))
	{
		GameEngine::engine.getDevice()->getSceneManager()->setActiveCamera(player->getCamera());
	}

	if(GameEngine::handler.keyFired(irr::KEY_F2))
	{
		GameEngine::engine.getDevice()->getSceneManager()->setActiveCamera(Menucamera);
	}

	if(GameEngine::handler.keyFired(irr::KEY_F3))
	{
		GameEngine::engine.getDevice()->getSceneManager()->setActiveCamera(Flycamera);
	}

	if(GameEngine::handler.keyFired(irr::KEY_F9))
	{
		workLight->setVisible(!workLight->isVisible());
	}

	if(GameEngine::handler.keyFired(irr::KEY_F10))
	{
		spinningLight->setVisible(!spinningLight->isVisible());
	}

	if(GameEngine::handler.keyFired(irr::KEY_F11))
	{
		level->toggleLighting(!level->isLit());
	}

	if(GameEngine::handler.keyFired(irr::KEY_KEY_R))
	{
		reset();
	}

	//debug physics objects
	if(GameEngine::handler.keyDown(irr::KEY_F5))
	{
		new Box(this,btVector3(-75.0f + ((((float) rand()) / ((float) RAND_MAX))*150.0f),100.0f,-75.0f + ((((float) rand()) / ((float) RAND_MAX))*150.0f)),irr::core::vector3df(10.0f,10.0f,10.0f),10.0f);
	}
	if(GameEngine::handler.keyFired(irr::KEY_F6))
	{
		new Box(this,btVector3(0,30,0),irr::core::vector3df(10.0f,10.0f,10.0f),10.0f);
	}
	if(GameEngine::handler.keyFired(irr::KEY_F7)){
		irr::scene::ICameraSceneNode* cam = GameEngine::engine.getDevice()->getSceneManager()->getActiveCamera();
		Box* bx = new Box(this,
			GameEngine::Physics::irrVec3ToBtVec3(cam->getAbsolutePosition()),
			irr::core::vector3df(30.0f,30.0f,30.0f),
			100.0f
		);
		irr::core::vector3df start = cam->getPosition();
		irr::core::vector3df end = (cam->getTarget() - start);
		end.normalize();
		bx->getRB()->setLinearVelocity(GameEngine::Physics::irrVec3ToBtVec3(end) * 100.0f);
	}

	//Has the player died?
	if(player->getHealth() <= 0 || !player->isAlive())
	{
		GameOver();
	}
	
	if(GameEngine::handler.keyFired(irr::KEY_RETURN))
	{
		// Change State
		Game::changeState("menu");
	}

	if(_gameover== false && _gamewon== false)
	{
	 _entityManager->update(delta);
	}
}


void Main_Scene::render()
{

}

// Removes all new created Entities, Resets everything to starting positions.
void Main_Scene::reset()
{
	std::cerr << "Game reset" << std::endl;
	irr::core::stringw str = "Game reset";
	GameEngine::UI::displayTextMessage(str,2000);

	//reset player position and health
	player->setHealth(100.0f);
	player->getController()->warp(btVector3(0,10,0));
	player->setAlive(true);

	//TODO Reset all game Entities
	_gameover = false;
	_gamewon = false;


	//Fade In
    fader->fadeIn(7000);

	//TODO, delete surplus entities
}


void Main_Scene::GameOver()
{
	if(_gameover == false)
	{
		std::cerr << "Game is over" << std::endl;
		irr::core::stringw str = "Game is over";
		GameEngine::UI::displayTextMessage(str,2000);
		fader->fadeOut(1000);
	}
	_gameover = true;
}


void Main_Scene::GameWon()
{
	if(!_gamewon)
	{

		std::cerr << "Game has been won" << std::endl;
		irr::core::stringw str = "Game is has been won by player";
		GameEngine::UI::displayTextMessage(str,2000);
		fader->fadeOut(3000);
		
	}
	_gamewon = true;
}