#pragma once
#include "Main_Scene.h"
#include <iostream>
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
#include "Box.h"
#include "Pathfinder.h"

irr::scene::ICameraSceneNode* Flycamera;
irr::scene::ICameraSceneNode* Menucamera;

bool Main_Scene::_gameover;
bool Main_Scene::_gamewon;
bool Main_Scene::_gamepaused;

Player* Main_Scene::player;
Level* level;
irr::gui::IGUIInOutFader* fader;

Main_Scene::Main_Scene():Scene("main")
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
	std::cout << "Main_Scene initialize" << std::endl;

	irr::scene::ISceneManager* smgr = GameEngine::engine.getDevice()->getSceneManager();

	//Cameras
	Flycamera = smgr->addCameraSceneNodeFPS();
	Flycamera->setPosition(irr::core::vector3df(0,100,0));
	Flycamera->setFarValue(10000.0f);
	
	Menucamera = smgr->addCameraSceneNode(0,irr::core::vector3df(0,100,223),irr::core::vector3df(0,100,0));

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

	for(int i = 0; i < 5; i++)
	{
		new Enemy(this,Pathfinder::getResolvedLocation(Pathfinder::getDarkLocation()));
	}
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

	if(level != nullptr )
	{
		delete level;
		level = NULL;
	}
	
	if(fader != nullptr )
	{
		fader->remove();
		fader = NULL;
	}

	_entityManager->shutdown();
}

// Run per-frame game logic.
void Main_Scene::update(float delta)
{
	
	//display player health
	irr::core::stringw str = "Player Health: ";
	str += player->getHealth();
	GameEngine::UI::displayTextMessage(str,0);

	// Toggle the pause state
	if(GameEngine::handler.keyFired(irr::KEY_KEY_P) || GameEngine::handler.keyFired(irr::KEY_PAUSE))
	{
		//TODO fix this, it's completely broken. Physics doesn't pause.
		_gamepaused = !_gamepaused;
		GameEngine::UI::displayTextMessage(irr::core::stringw("Game Paused"),100);
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

	// Has the player died?
	if(!_gameover && (player->getHealth() <= 0 || !player->isAlive()) )
	{
		GameOver();
	}

	// Has the player won?
	else if(!_gamewon && level->allBeaconsLit())
	{
		GameWon();
	}

	// Only update if the game is still playing
	if(!_gameover && !_gamewon && !_gamepaused)
	{
		_entityManager->update(delta);
	}
	
	if(GameEngine::handler.keyFired(irr::KEY_RETURN))
	{
		// Change Scene
		Game::changeScene("menu");
	}

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