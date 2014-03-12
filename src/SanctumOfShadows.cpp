#include "SanctumOfShadows.h"
#include "Box.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Beacon.h"
#include <btBulletDynamicsCommon.h>


bool SanctumOfShadows::_gameover;
irr::scene::ICameraSceneNode* camera;
irr::scene::ICameraSceneNode* Flycamera;
irr::scene::ICameraSceneNode* Menucamera;
irr::scene::ILightSceneNode* workLight;
bool _flying;
Level* level;
Player* SanctumOfShadows::player;
Enemy* enemy;
bool SanctumOfShadows::init(){
	std::wcout <<  _gameTitle << " Game code init" << std::endl;
	
	if (!GameEngine::engine.loadContent()){
		return false;
	}

	irr::scene::ISceneManager* smgr = GameEngine::engine.getDevice()->getSceneManager();

	//load the level
	level = new Level();
	level->loadContent();

	//Cameras
	camera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNodeFPS();
	camera->setPosition(irr::core::vector3df(0,100,0));

	Flycamera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNodeFPS();
	Flycamera->setPosition(irr::core::vector3df(0,100,0));
	Flycamera->setFarValue(10000.0f);

	Menucamera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNode(0,irr::core::vector3df(0,100,223),irr::core::vector3df(0,100,0));
	workLight = smgr->addLightSceneNode(0, irr::core::vector3df(0,100.0f,0), irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 3000.0f);

	irr::video::SLight& sl= workLight->getLightData();
	//constant, linear and quadratic
	sl.Attenuation = irr::core::vector3df(0,0,0.0000001f);
	/*
	sl.Type = irr::video::E_LIGHT_TYPE::ELT_SPOT;
	//rotate this, find out whats going on
	sl.Direction = irr::core::vector3df(1,-1,0);
	sl.DiffuseColor = irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f);
	sl.AmbientColor = irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f);
	sl.SpecularColor = irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f);
	sl.InnerCone = 60.0f;
	sl.OuterCone = 90.0f;
	sl.Falloff =  1000.0f;
	*/
	std::cout << " Radius: " << sl.Radius << " Type: " << sl.Type << 
		" Direction: " << sl.Direction.X << ", " << sl.Direction.Y << ", " << sl.Direction.Z << ") "<<
		" Attenuation: " << sl.Attenuation.X << ", " << sl.Attenuation.Y << ", " << sl.Attenuation.Z << ") " 
		<<std::endl;  
	
	
	// create light
	irr::scene::ISceneNode* Lightnode = 0;
	Lightnode = smgr->addLightSceneNode(0, irr::core::vector3df(0,100,0), irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 1000.0f);
	irr::scene::ISceneNodeAnimator* anim = 0;
	anim = smgr->createFlyCircleAnimator (irr::core::vector3df(0,100,0),300.0f);
	Lightnode->addAnimator(anim);
	anim->drop();

	// attach billboard sprite to light
	irr::scene::ISceneNode* LightSpriteNode = smgr->addBillboardSceneNode(Lightnode, irr::core::dimension2d<irr::f32>(50, 50));
	LightSpriteNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	LightSpriteNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	LightSpriteNode->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/particlewhite.bmp"));
	

	player = new Player(irr::core::vector3df(0,200.0f,0));
	Enemy::setPlayerRef(player);
	enemy = new Enemy(irr::core::vector3df(400.0f,200.0f,0));
	 Beacon(irr::core::vector3df(0,0,40.0f));
	//

	/*
	irr::scene::IMeshSceneNode* sphere = smgr->addSphereSceneNode(10.0f);
	sphere->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	btCollisionShape* fallShape = new btSphereShape(10.0);
	GameEngine::MotionState* fallMotionState = new GameEngine::MotionState(btTransform(btQuaternion(0.0, 0.0, 0.0, 1.0), btVector3(0.0, 50.0, 0.0)), sphere);
	btScalar mass = 10.0;
	btVector3 inertia(0.0, 0.0, 0.0);
	fallShape->calculateLocalInertia(mass, inertia);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, inertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	GameEngine::Physics::world->addRigidBody(fallRigidBody);
	*/
	//


	return true;
}

bool SanctumOfShadows::update(float delta){
	//TODO, move some of this to baseclass

	//display player health

	std::cerr << player->getHealth() << std::endl;


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
		GameEngine::engine.getDevice()->getSceneManager()->setActiveCamera(camera);
	}
	if(GameEngine::handler.keyFired(irr::KEY_F3))
	{
		GameEngine::engine.getDevice()->getSceneManager()->setActiveCamera(Flycamera);
	}
	if(GameEngine::handler.keyFired(irr::KEY_F4))
	{
		GameEngine::engine.getDevice()->getSceneManager()->setActiveCamera(Menucamera);
	}
	//debug random physics objects
	if(GameEngine::handler.keyDown(irr::KEY_F5))
	{
		new Box(btVector3(-75.0f + ((((float) rand()) / ((float) RAND_MAX))*150.0f),100.0f,-75.0f + ((((float) rand()) / ((float) RAND_MAX))*150.0f)),irr::core::vector3df(10.0f,10.0f,10.0f),10.0f);
	}
	if(GameEngine::handler.keyFired(irr::KEY_F6))
	{
		new Box(btVector3(0,30,0),irr::core::vector3df(10.0f,10.0f,10.0f),10.0f);
	}
	//worklight
	if(GameEngine::handler.keyFired(irr::KEY_F8))
	{
		workLight->setVisible(!workLight->isVisible());
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


	return true;
}

void SanctumOfShadows::reset(){

}

void SanctumOfShadows::GameOver()
{
	if(_gameover == false)
	{
	std::cerr << "Game is over" << std::endl;
	
	irr::scene::ISceneNode* DeadSpriteNode = GameEngine::engine.getDevice()->getSceneManager()->addBillboardSceneNode(player->getNode(), irr::core::dimension2d<irr::f32>(150, 100),irr::core::vector3df(0,0,1));
	DeadSpriteNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	DeadSpriteNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	DeadSpriteNode->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/GameOver.PNG"));
	}
	_gameover = true;
}
