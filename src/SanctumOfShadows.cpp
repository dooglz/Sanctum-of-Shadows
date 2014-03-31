#include "SanctumOfShadows.h"
#include "Main_Scene.h"
#include "Menu_Scene.h"

SanctumOfShadows::SanctumOfShadows()
{
	_gameTitle = L"SanctumOfShadows";
	_resolution  = irr::core::dimension2d<irr::u32>(1280, 720);
}

// Creates Required Entities.
bool SanctumOfShadows::init(){
	std::wcout <<  _gameTitle << " Game code init" << std::endl;

	addScene( new Main_Scene() );
	addScene( new Menu_Scene() );

	_loadingImg = GameEngine::engine.getDevice()->getGUIEnvironment()->addImage(irr::core::rect<irr::s32>(0,0,_resolution.Width,_resolution.Height),0);
	//TODO checks this loads.
	_loadingTexture = GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_loading.png");
	_loadingImg->setImage(_loadingTexture );
	_loadingImg->setScaleImage(true);

	changeScene("menu");

	return true;
}

// Run per-frame Scene Independent game logic.
bool SanctumOfShadows::update(float delta){
	
	processScenes();
	
	if(GameEngine::handler.keyFired(irr::KEY_ESCAPE))
	{
		GameEngine::engine.stop();
	}

	if(GameEngine::handler.keyFired(irr::KEY_F8))
	{
		GameEngine::engine.setBulletDebugDrawing(!GameEngine::engine.getBulletDebugDrawing());
	}
	
	if(_sceneLoaded)
	{
		_activeScene->update(delta);
	}

	return true;
}

// Destructor
SanctumOfShadows::~SanctumOfShadows()
{

}
