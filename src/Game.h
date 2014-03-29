#pragma once
#include <irrlicht.h>
#include <iostream>
#include <unordered_map>
#include "GameState.h"


/*! \brief Baseclass for gamelogic, bridge between engine and game code, think of this as also a Game state manager.
 * \ingroup Engine
 */
class Game{
protected:
	//! Title of the game
	std::wstring _gameTitle;

	//! Starting dimensions
	irr::core::dimension2d<irr::u32> _resolution;

	irr::gui::IGUIImage* _loadingImg;
	irr::video::ITexture* _loadingTexture;

	static GameEngine::GameState* _activeState;
	static GameEngine::GameState* _targetState;

	static std::unordered_map<std::string, GameEngine::GameState*> _states;

	static GameEngine::GameState* findState(std::string a);
	static void addState(GameEngine::GameState* newState);
	static bool _stateLoaded;

public:

	//! Constructor.
	Game(){};
	
	//! Destructor.
	~Game();

	//! Initialise.
	virtual bool init() = 0;

	//! Run per-frame State Independent game logic.
	virtual bool update(float delta) = 0;

	//! Returns _gameTitle. 
	std::wstring getGametitle();

	//! Returns _resolution. 
	irr::core::dimension2d<irr::u32> getResolution();

	//! Returns the current game state.
	GameEngine::GameState* getActiveState();

	static void changeState(GameEngine::GameState* newState);

	static void changeState(std::string newState);
	
	void processStates();
};