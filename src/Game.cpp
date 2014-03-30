#pragma once
#include "Game.h"
#include "UI.h"

GameEngine::Scene* Game::_activeScene;
GameEngine::Scene* Game::_targetScene;
std::unordered_map<std::string, GameEngine::Scene*>  Game::_scenes;
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

void Game::changeScene(GameEngine::Scene* newScene)
{
	//transition into loading state
	GameEngine::UI::clear();
	_sceneLoaded = false;
	_targetScene = newScene;
}

void Game::changeScene(std::string newScene)
{
	changeScene(findScene(newScene));
}

GameEngine::Scene* Game::findScene(std::string sceneName)
{
	auto found = _scenes.find(sceneName);
	if(found != _scenes.end())
	{
		return found->second;
	}
	//TODO handle this better.
	std::cout << "Couldn't Locate Scene: "<< sceneName << std::endl;
	return NULL;
}

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