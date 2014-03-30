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
	//! Title of the game.
	std::wstring _gameTitle;

	//! Starting dimensions.
	irr::core::dimension2d<irr::u32> _resolution;

	//! Image object to show during loading.
	irr::gui::IGUIImage* _loadingImg;

	//! Texture to display on _loadingImg.
	irr::video::ITexture* _loadingTexture;

	//! The currently active Scene.
	static GameEngine::Scene* _activeScene;

	//! The Scene to transition into.
	static GameEngine::Scene* _targetScene;

	//! Map containing all scenes, identified by their name. 
	static std::unordered_map<std::string, GameEngine::Scene*> _scenes;

	//! Find a scene by name.
	static GameEngine::Scene* findScene(std::string sceneName);

	//! Register a new scene.
	static void addScene(GameEngine::Scene* newScene);

	//! Is the scene we are transitioning into loaded?
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

	//! Transition into a different scene.
	static void changeScene(GameEngine::Scene* newScene);

	//! Transition into a different scene, identified by name.
	static void changeScene(std::string newScene);
	
	//! Process scene transition logic, should be called every frame.
	void processScenes();
};