#pragma once
#include "Game.h"
#include "UI.h"
#include "Utilities.h"

// The currently active Scene.
GameEngine::Scene* Game::_activeScene;

// The Scene to transition into.
GameEngine::Scene* Game::_targetScene;

// Map containing all scenes, identified by their name. 
std::unordered_map<std::string, GameEngine::Scene*>  Game::_scenes;

// Is the scene we are transitioning into loaded?
bool Game::_sceneLoaded;

//! Returns _gameTitle. 
std::wstring Game::getGametitle(){
	return _gameTitle;
}

//! Returns _resolution. 
irr::core::dimension2d<irr::u32> Game::getResolution(){
	return _resolution;
}

//! Returns the current game Scene.
GameEngine::Scene* Game::getActiveScene(){
	return _activeScene;
}

// Transition into a different scene.
void Game::changeScene(GameEngine::Scene* newScene)
{
	//transition into loading state
	GameEngine::UI::clear();
	_sceneLoaded = false;
	_targetScene = newScene;
}

// Transition into a different scene, identified by name.
void Game::changeScene(std::string newScene)
{
	changeScene(findScene(newScene));
}

// Find a scene by name.
GameEngine::Scene* Game::findScene(std::string sceneName)
{
	auto found = _scenes.find(sceneName);
	if(found != _scenes.end())
	{
		return found->second;
	}
	//TODO handle this better.
	if(VERBOSE_lEVEL > 0)
	{
		std::cout << "Couldn't Locate Scene: "<< sceneName << std::endl;
	}
	return NULL;
}

// Register a new scene
void Game::addScene(GameEngine::Scene* newScene)
{
	//already stored?
	if(_scenes.find(newScene->getName()) != _scenes.end())
	{
		std::cerr << "Error registering new Scene: " << newScene->getName()
			<< " Scene with same name already stored"<< std::endl;
		return;
	}
	//nope, store the new Scene.
	_scenes[newScene->getName()] = newScene;
}

// Process scene transition logic, should be called every frame.
void Game::processScenes()
{
	//Are we transitioning
	if(!_sceneLoaded)
	{
		//Has the loading screen loaded?
		if(_loadingImg->isVisible())
		{
			//We don't have parallel loading threads, so we will hang around here while we load.
			if (_activeScene != nullptr )
			{
				_activeScene->flush();
			}
			if (_targetScene != nullptr )
			{
				_targetScene->initialize();
			}
			else
			{
				//Oh Fiddlesticks. TODO
			}

			_sceneLoaded = true;
			_activeScene = _targetScene;
			_loadingImg->setVisible(false);

		}
		else
		{
			_loadingImg->setVisible(true);
			return;
		}
	}
}

// Destructor
Game::~Game()
{
	std::unordered_map<std::string, GameEngine::Scene*>::iterator iter = _scenes.begin();
	for(; iter != _scenes.end(); ++iter)
	{
		//delete Scenes, free memory
		if(iter->second != nullptr )
		{
			delete iter->second;
			iter->second = NULL;
		}
	}
	_scenes.clear();

	if (_loadingImg != nullptr )
	{
		_loadingImg->remove();
		_loadingImg = NULL;
	}
	if (_loadingTexture != nullptr )
	{
		_loadingTexture->drop();
		_loadingTexture = NULL;
	}

}