#pragma once
#include "Game.h"

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
