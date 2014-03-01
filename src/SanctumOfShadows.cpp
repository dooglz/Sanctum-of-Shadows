#include "SanctumOfShadows.h"
#include "Box.h"
#include "Level.h"
#include "Player.h"

#include <btBulletDynamicsCommon.h>

irr::scene::ICameraSceneNode* camera;
irr::scene::ICameraSceneNode* Flycamera;
irr::scene::ICameraSceneNode* Menucamera;
bool _flying;
Level* level = new Level();
Player* player;

bool SanctumOfShadows::init(){
	std::wcout <<  _gameTitle << " Game code init" << std::endl;
	
	if (!GameEngine::engine.loadContent()){
		return false;
	}

	irr::scene::ISceneManager* smgr = GameEngine::engine.getDevice()->getSceneManager();

	//Add a cube at origin, for bearings
	irr::scene::IAnimatedMesh* cube = smgr->getMesh("models/cube1.obj");
	if (!cube)
	{
		std::cerr << "Error loading Mesh" << std::endl;
		return false;
	}
	irr::scene::ISceneNode* originBox = smgr->addMeshSceneNode(cube);
	originBox->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	originBox->setScale(irr::core::vector3df(10,10,10));
	
	//load the level
	level->loadContent();

	//Cameras
	camera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNodeFPS();
	camera->setPosition(irr::core::vector3df(0,100,0));

	Flycamera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNodeFPS();
	Flycamera->setPosition(irr::core::vector3df(0,100,0));
	Flycamera->setFarValue(10000.0f);

	Menucamera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNode(0,irr::core::vector3df(0,100,223),irr::core::vector3df(0,100,0));

	// create light
	irr::scene::ISceneNode* Lightnode = 0;
	Lightnode = smgr->addLightSceneNode(0, irr::core::vector3df(0,100,0), irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 1000.0f);
	irr::scene::ISceneNodeAnimator* anim = 0;
	anim = smgr->createFlyCircleAnimator (irr::core::vector3df(0,100,0),200.0f);
	Lightnode->addAnimator(anim);
	anim->drop();

	// attach billboard sprite to light
	irr::scene::ISceneNode* LightSpriteNode = smgr->addBillboardSceneNode(Lightnode, irr::core::dimension2d<irr::f32>(50, 50));
	LightSpriteNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	LightSpriteNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	LightSpriteNode->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/particlewhite.bmp"));


	player = new Player();
	player->intitalise(irr::core::vector3df(0,200.0f,0));


	return true;
}

bool a,b;
bool SanctumOfShadows::update(float delta){
	//adding player update

	//player->update(delta);
	player->update2(delta);
	//TODO, move some of this to baseclass
	if(GameEngine::handler.keyDown(irr::KEY_F1)){
		GameEngine::engine.getDevice()->getSceneManager()->setActiveCamera(player->getCamera());
	}
	if(GameEngine::handler.keyDown(irr::KEY_F2)){
		GameEngine::engine.getDevice()->getSceneManager()->setActiveCamera(camera);
	}
	if(GameEngine::handler.keyDown(irr::KEY_F3)){
		GameEngine::engine.getDevice()->getSceneManager()->setActiveCamera(Flycamera);
	}
	if(GameEngine::handler.keyDown(irr::KEY_F4)){
		GameEngine::engine.getDevice()->getSceneManager()->setActiveCamera(Menucamera);
	}
	if(GameEngine::handler.keyDown(irr::KEY_F5)){
		new Box(btVector3(-75.0f + ((((float) rand()) / ((float) RAND_MAX))*150.0f),100.0f,-75.0f + ((((float) rand()) / ((float) RAND_MAX))*150.0f)),irr::core::vector3df(10.0f,10.0f,10.0f),10.0f);
	}
	if(!a && GameEngine::handler.keyDown(irr::KEY_F6)){
		new Box(btVector3(0,30,0),irr::core::vector3df(10.0f,10.0f,10.0f),10.0f);
		a = true;
	}
	if(GameEngine::handler.keyUp(irr::KEY_F6)){
		a = false;
	}

	if(!b && GameEngine::handler.keyDown(irr::KEY_F7)){
		irr::scene::ICameraSceneNode* cam = GameEngine::engine.getDevice()->getSceneManager()->getActiveCamera();
		Box* bx = new Box(
			GameEngine::Physics::irrVec3ToBtVec3(cam->getAbsolutePosition()),
			irr::core::vector3df(10.0f,10.0f,10.0f),
			10.0f
		);
		irr::core::vector3df start = cam->getPosition();
		irr::core::vector3df end = (cam->getTarget() - start);
		end.normalize();
		bx->getRB()->setLinearVelocity(GameEngine::Physics::irrVec3ToBtVec3(end) * 100.0f);
		b = true;
	}
		if(GameEngine::handler.keyUp(irr::KEY_F7)){
		b = false;
	}


	return true;
}

void SanctumOfShadows::reset(){

}
