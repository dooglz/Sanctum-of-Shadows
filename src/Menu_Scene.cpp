#include "Menu_Scene.h"
#include "Engine.h"
#include "Game.h"

irr::gui::IGUIImage* img;
irr::video::ITexture* tex;

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
	tex = GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_spiral.jpg");
	return true;
}

void Menu_Scene::initialize()
{
	std::cout << "Menu_Scene initialize" << std::endl;
	loadContent();
	//Don't drop this pointer, Irrlicht hates it.
	img = GameEngine::engine.getDevice()->getGUIEnvironment()->addImage(irr::core::rect<irr::s32>(200,200,500,500),0);
	img->setImage(tex);
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