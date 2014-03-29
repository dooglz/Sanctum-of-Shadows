#include "Menu_Scene.h"
#include "Engine.h"
#include "Game.h"

irr::gui::IGUIImage* img;
irr::scene::ICameraSceneNode* menucam;
irr::scene::ISceneNode* logoNode;

Menu_Scene::Menu_Scene():GameState("menu")
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
	std::cout << "Menu_Scene initialize" << std::endl;
		irr::scene::ISceneManager* smgr = GameEngine::engine.getDevice()->getSceneManager();

	logoNode = smgr->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(1280, 163));
	//logoNode->setMaterialFlag(irr::video::EMF_TEXTURE_WRAP, true);
	logoNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	logoNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	//logoNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	logoNode->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/Logo1.jpg"));
//	logoNode->getMaterial(0).getTextureMatrix(0).setTextureScale(5.0f,5.0f);

	menucam = smgr->addCameraSceneNode(0,irr::core::vector3df(0,0,500),irr::core::vector3df(0,0,0));
	irr::scene::ILightSceneNode* workLight = smgr->addLightSceneNode(0, irr::core::vector3df(0,0,0), irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 10000.0f);

	loadContent();
}

void Menu_Scene::flush()
{
	std::cout << "Menu_Scene flush" << std::endl;
}

void Menu_Scene::update(float delta)
{
	GameEngine::UI::displayTextMessage(irr::core::stringw("This is the Menu"),0);
	if(GameEngine::handler.keyFired(irr::KEY_RETURN))
	{
		// Change State
		Game::changeState("main");
	}
	if(GameEngine::handler.keyFired(irr::KEY_SPACE))
	{
		GameEngine::UI::displayTextMessage(irr::core::stringw("Space pressed"),100);
	}
}

void Menu_Scene::render()
{

}