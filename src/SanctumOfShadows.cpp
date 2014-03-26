#include "SanctumOfShadows.h"
#include "Box.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Beacon.h"
#include <btBulletDynamicsCommon.h>


bool SanctumOfShadows::_gameover;
irr::scene::ICameraSceneNode* Flycamera;
irr::scene::ICameraSceneNode* Menucamera;

irr::gui::IGUIInOutFader* fader;

//debug lights
irr::scene::ILightSceneNode* workLight;
irr::scene::ILightSceneNode* spinningLight;

bool _flying;
Level* level;
Player* SanctumOfShadows::player;
Enemy* enemy;

// Creates Required Entities.
bool SanctumOfShadows::init(){

	std::wcout <<  _gameTitle << " Game code init" << std::endl;

	irr::scene::ISceneManager* smgr = GameEngine::engine.getDevice()->getSceneManager();

	//load the level
	level = new Level();
	level->loadContent();
	level->intitalise();

	//Cameras
	Flycamera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNodeFPS();
	Flycamera->setPosition(irr::core::vector3df(0,100,0));
	Flycamera->setFarValue(10000.0f);

	Menucamera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNode(0,irr::core::vector3df(0,100,223),irr::core::vector3df(0,100,0));
	workLight = smgr->addLightSceneNode(0, irr::core::vector3df(0,200.0f,0), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 1000.0f);
	
	// create spinning light
	spinningLight = smgr->addLightSceneNode(0, irr::core::vector3df(0,300.0f,0), irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 1000.0f);
	irr::scene::ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator (irr::core::vector3df(0,50,0),300.0f);
	spinningLight->addAnimator(anim);
	anim->drop();
	irr::scene::ISceneNode* LightSpriteNode = smgr->addBillboardSceneNode(spinningLight, irr::core::dimension2d<irr::f32>(50, 50));
	LightSpriteNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	LightSpriteNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	LightSpriteNode->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/particlewhite.bmp"));
	
	//Game Entities
	player = new Player(irr::core::vector3df(0,200.0f,0));
	enemy = new Enemy(irr::core::vector3df(400.0f,200.0f,0));
	//

	//Beacon* b = new Beacon(irr::core::vector3df(0,0,500.0f));
	
	irr::core::stringw str = "Game Initialised";
	GameEngine::UI::displayTextMessage(str,2000);

	//fader
	fader = GameEngine::engine.getDevice()->getGUIEnvironment()->addInOutFader();
    fader->setColor(irr::video::SColor(0,0,0,0));

	reset();

	return true;
}

// Run per-frame game logic.
bool SanctumOfShadows::update(float delta){

	//TODO, move some of this to baseclass

	//display player health
	irr::core::stringw str = "Player Health: ";
	str += player->getHealth();
	GameEngine::UI::displayTextMessage(str,0);


	if(GameEngine::handler.keyFired(irr::KEY_KEY_R))
	{
		reset();
	}

	if(GameEngine::handler.keyFired(irr::KEY_ESCAPE))
	{
		GameEngine::engine.stop();
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


	//debug physics objects
	if(GameEngine::handler.keyDown(irr::KEY_F5))
	{
		new Box(btVector3(-75.0f + ((((float) rand()) / ((float) RAND_MAX))*150.0f),100.0f,-75.0f + ((((float) rand()) / ((float) RAND_MAX))*150.0f)),irr::core::vector3df(10.0f,10.0f,10.0f),10.0f);
	}
	if(GameEngine::handler.keyFired(irr::KEY_F6))
	{
		new Box(btVector3(0,30,0),irr::core::vector3df(10.0f,10.0f,10.0f),10.0f);
	}
	if(GameEngine::handler.keyFired(irr::KEY_F7)){
		irr::scene::ICameraSceneNode* cam = GameEngine::engine.getDevice()->getSceneManager()->getActiveCamera();
		Box* bx = new Box(
			GameEngine::Physics::irrVec3ToBtVec3(cam->getAbsolutePosition()),
			irr::core::vector3df(100.0f,100.0f,100.0f),
			100.0f
		);
		irr::core::vector3df start = cam->getPosition();
		irr::core::vector3df end = (cam->getTarget() - start);
		end.normalize();
		bx->getRB()->setLinearVelocity(GameEngine::Physics::irrVec3ToBtVec3(end) * 100.0f);
	}

	//debug lights
	if(GameEngine::handler.keyFired(irr::KEY_F9))
	{
		workLight->setVisible(!workLight->isVisible());
	}
	if(GameEngine::handler.keyFired(irr::KEY_F10))
	{
		spinningLight->setVisible(!spinningLight->isVisible());
	}

	return true;
}

// Removes all new created Entities, Resets everything to starting positions.
void SanctumOfShadows::reset()
{
	std::cerr << "Game reset" << std::endl;
	irr::core::stringw str = "Game reset";
	GameEngine::UI::displayTextMessage(str,2000);

	//reset player position and health
	player->setHealth(100.0f);
	player->getController()->warp(btVector3(0,10,0));

	//TODO Reset all game Entities
	_gameover = false;
	player->setAlive(true);
	//Fade In
  //  fader->fadeIn(8000);
	//fader->drop();

	//TODO, delete surplus entities
}

// Move to Gameover State.
void SanctumOfShadows::GameOver()
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

// Destructor
SanctumOfShadows::~SanctumOfShadows()
{
	fader->drop();
	fader = NULL;
	
	Menucamera->drop();
	workLight->drop();
	spinningLight->drop();

	delete level;
	level = NULL;

	delete player;
	player = NULL;

	delete enemy;
	enemy = NULL;

	Flycamera->drop();
}
