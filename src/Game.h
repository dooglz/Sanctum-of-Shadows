#pragma once
#include <irrlicht.h>
#include <iostream>
#include <unordered_map>
#include "Scene.h"


/*! \brief Baseclass for gamelogic, bridge between engine and game code, think of this also as a Scene manager.
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

	static GameEngine::Scene* _activeScene;
	static GameEngine::Scene* _targetScene;

	static std::unordered_map<std::string, GameEngine::Scene*> _scenes;

	static GameEngine::Scene* findScene(std::string sceneName);
	static void addScene(GameEngine::Scene* newScene);
	static bool _sceneLoaded;

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

	//! Returns the current game Scene.
	GameEngine::Scene* getActiveScene();

	static void changeScene(GameEngine::Scene* newScene);

	static void changeScene(std::string newScene);
	
	void processScenes();
};