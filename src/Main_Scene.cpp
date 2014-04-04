#pragma once
#include "Main_Scene.h"
#include <iostream>
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
#include "Pathfinder.h"
#include "Utilities.h"


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
	if(VERBOSE_lEVEL > 1)
	{
		std::cout << "Main_Scene constructor" << std::endl;
	}
}

// Destructor
Main_Scene::~Main_Scene()
{
	if(VERBOSE_lEVEL > 1)
	{
		std::cout << "Main_Scene destructor" << std::endl;
	}
	flush();
}

bool Main_Scene::loadContent()
{
	if(VERBOSE_lEVEL > 1)
	{
		std::cout << "Main_Scene loadContent" << std::endl;
	}
	return true;
}

void Main_Scene::initialize()
{
	if(VERBOSE_lEVEL > 1)
	{
		std::cout << "Main_Scene initialize" << std::endl;
	}

	_gameover = false;
	_gamewon = false;
	_gamepaused = false;

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
	player->setHealth(100.0f);
	player->getController()->warp(btVector3(0,10,0));
	player->setAlive(true);
	Enemy::setPlayer(player);

	for(int i = 0; i < 250; i++)
	{
		new Enemy(this,Pathfinder::getResolvedLocation(Pathfinder::getDarkLocation()));
	}

	GameEngine::UI::displayTextMessage(irr::core::stringw("Press H for help"),1000);
	
	//Spookysound
	GameEngine::Engine::soundengine->play2D("sounds/SOS_cave_amb_2.ogg", true);

}

void Main_Scene::flush()
{
	if(VERBOSE_lEVEL > 1)
	{
		std::cout << "Main_Scene Flush" << std::endl;
	}

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
	GameEngine::Engine::soundengine->stopAllSounds();
}

// Run per-frame game logic.
void Main_Scene::update(float delta)
{

	if(DEVELOPER_MODE)
	{
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

		//toggle level lighting
		if(GameEngine::handler.keyFired(irr::KEY_F11))
		{
			level->toggleLighting(!level->isLit());
		}

	}

	// Show a help message
	if(GameEngine::handler.keyFired(irr::KEY_KEY_H))
	{
		displayHelp();
	}

	// Return to menu
	if(GameEngine::handler.keyFired(irr::KEY_ESCAPE))
	{
		Game::changeScene("menu");
	}

	// Toggle the pause state
	if(GameEngine::handler.keyFired(irr::KEY_KEY_P) || GameEngine::handler.keyFired(irr::KEY_PAUSE))
	{
		_gamepaused = !_gamepaused;
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

	level->displayProgress();

	// Only update if the game is still playing
	if(!_gameover && !_gamewon && !_gamepaused)
	{
		//update entityManage
		_entityManager->update(delta);
	}
	
	if(_gamepaused)
	{
		GameEngine::UI::displayBigMessage(irr::core::stringw("Game Paused"),1);
	}
	
	if(_gamewon || _gameover)
	{
		GameEngine::UI::displayTextMessage(irr::core::stringw("Press Space to Return to menu"),0);
		
		if(_gameover)
		{
			GameEngine::UI::displayBigMessage(irr::core::stringw("You have Died"),1);
		}

		if(_gamewon)
		{
			GameEngine::UI::displayBigMessage(irr::core::stringw("You have won"),1);
		}
		
		if(GameEngine::handler.keyFired(irr::KEY_SPACE))
		{
			Game::changeScene("menu");
		}
	}

}

// Handle the loose scenario
void Main_Scene::GameOver()
{
	if(_gameover == false)
	{
		if(VERBOSE_lEVEL > 1)
		{
			std::cerr << "Game is over" << std::endl;
		}
		fader->fadeOut(1000);
	}
	_gameover = true;
}

// Handle the win scenario
void Main_Scene::GameWon()
{
	if(!_gamewon)
	{
		if(VERBOSE_lEVEL > 1)
		{
			std::cerr << "Game has been won" << std::endl;
		}
		fader->fadeOut(3000);
	}
	_gamewon = true;
}


// Show a random help message
void Main_Scene::displayHelp()
{
	irr::core::stringw strings[6];

	strings[0] = "Use the wasd keys to move";
	strings[1] = "Use space to attack";
	strings[2] = "Approach beacons to activate them!";
	strings[3] = "Press 'P' to pause";
	strings[4] = "Press 'Esc' to quit";
	strings[5] = "Beacons Regerate your Health and Fuel";

	std::uniform_int_distribution<int> distribution(0, 5);

	GameEngine::UI::displayTextMessage(strings[distribution(GameEngine::Engine::generator)],400);
}