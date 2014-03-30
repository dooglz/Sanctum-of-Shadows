#include "Menu_Scene.h"
#include "Engine.h"
#include "Game.h"

Menu_Scene::Menu_Scene():Scene("menu")
{
	std::cout << "Menu_Scene constructor" << std::endl;
}

Menu_Scene::~Menu_Scene()
{
	std::cout << "Menu_Scene Destructor" << std::endl;
	flush();
}

bool Menu_Scene::loadContent()
{
	std::cout << "Menu_Scene loadContent" << std::endl;
	return true;
}

void Menu_Scene::initialize()
{
	loadContent();
	std::cout << "Menu_Scene initialize" << std::endl;

	irr::scene::ISceneManager* smgr = GameEngine::engine.getDevice()->getSceneManager();
	
	// Floating Logo
	logoNode = smgr->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(1280, 163));
	logoNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	logoNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	logoNode->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/Logo1.jpg"));

	//Camera
	menucam = smgr->addCameraSceneNode(0,irr::core::vector3df(0,0,500),irr::core::vector3df(0,0,0));
	irr::scene::ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator (irr::core::vector3df(0,0,700),200.0,0.0005f);
	menucam->addAnimator(anim);
	anim->drop();

	//Beacon
	menuBeacon = new Beacon(this,irr::core::vector3df(0,-150,500));
	menuBeacon->getNode()->setRotation(irr::core::vector3df(0,90.0f,0));
	menuBeacon->light(true);

	//Floor
	irr::scene::IAnimatedMesh* planeMesh = GameEngine::engine.getDevice()->getSceneManager()->addHillPlaneMesh("menufloormesh", irr::core::dimension2df(300.0f,300.0f), irr::core::dimension2du(8,8));
	irr::scene::IMesh* tangentMesh = GameEngine::engine.getDevice()->getSceneManager()->getMeshManipulator()->createMeshWithTangents(planeMesh->getMesh(0));
	floorNode = smgr->addMeshSceneNode(tangentMesh);
	floorNode->setPosition(irr::core::vector3df(0,-150,300));
	floorNode->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_cobble2_1024.jpg"));
	floorNode->setMaterialTexture(1, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_cobble2_1024_NRM.jpg"));
	floorNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	floorNode->setMaterialType(irr::video::EMT_NORMAL_MAP_SOLID);
	floorNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);

}

void Menu_Scene::flush()
{
	std::cout << "Menu_Scene flush" << std::endl;
	if (logoNode != nullptr )
	{
		logoNode->remove();
		logoNode = NULL;
	}

	if (menucam != nullptr )
	{
		menucam->remove();
		menucam = NULL;
	}

	if (floorNode != nullptr )
	{
		floorNode->remove();
		floorNode = NULL;
	}

	if (menuBeacon != nullptr )
	{
		menuBeacon->remove();
		delete menuBeacon;
		menuBeacon = NULL;
	}

	_entityManager->shutdown();

}

void Menu_Scene::update(float delta)
{
	GameEngine::UI::displayTextMessage(irr::core::stringw("Press Space to Begin"),0);
	if(GameEngine::handler.keyFired(irr::KEY_RETURN))
	{
		// Change Scene
		Game::changeScene("main");
	}
	if(GameEngine::handler.keyFired(irr::KEY_SPACE))
	{
		GameEngine::UI::displayTextMessage(irr::core::stringw("Space pressed"),100);
	}
}