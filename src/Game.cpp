#pragma once
#include "Game.h"

GameEngine::GameState* Game::_activeState;
GameEngine::GameState* Game::_targetState;
std::unordered_map<std::string, GameEngine::GameState*>  Game::_states;
bool Game::_stateLoaded;

//! Returns _gameTitle. 
std::wstring Game::getGametitle(){
	return _gameTitle;
}

//! Returns _resolution. 
irr::core::dimension2d<irr::u32> Game::getResolution(){
	return _resolution;
}

//! Returns the current game state.
GameEngine::GameState* Game::getActiveState(){
	return _activeState;
}

void Game::changeState(GameEngine::GameState* newState)
{
	//transition into loading state
	_stateLoaded = false;
	_targetState = newState;
}

void Game::changeState(std::string newState)
{
	changeState(findState(newState));
}

GameEngine::GameState* Game::findState(std::string a)
{
	auto found = _states.find(a);
	if(found != _states.end())
	{
		return found->second;
	}
	//TODO handle this better.
	std::cout << "Couldn't Locate Scene: "<< a << std::endl;
	return NULL;
}

void Game::addState(GameEngine::GameState* newState)
{
	//already stored?
	if(_states.find(newState->getName()) != _states.end())
	{
		std::cerr << "Error registering new State: " << newState->getName()
			<< " State with same name already stored"<< std::endl;
		return;
	}
	//nope, store the new state.
	_states[newState->getName()] = newState;
}

void Game::processStates()
{
	//Are we transitioning
	if(!_stateLoaded)
	{
		//Has the loading screen loaded?
		if(_LoadingImg->isVisible())
		{
			//We don't have parallel loading threads, so we will hang around here while we load.
			if (_activeState != nullptr )
			{
				_activeState->flush();
				delete _activeState;
			}
			if (_targetState != nullptr )
			{
				_targetState->initialize();
			}
			else
			{
				//Oh Fiddlesticks. TODO
			}

			_stateLoaded = true;
			_activeState = _targetState;
			_LoadingImg->setVisible(false);

		}
		else
		{
			_LoadingImg->setVisible(true);
			return;
		}
	}
}

Game::~Game()
{
	std::unordered_map<std::string, GameEngine::GameState*>::iterator iter = _states.begin();
	for(; iter != _states.end(); ++iter)
	{
		//delete states, free memory
		if(iter->second != nullptr )
		{
			delete iter->second;
			iter->second = NULL;
		}
	}
	_states.clear();
}