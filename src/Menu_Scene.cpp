#include "Menu_Scene.h"
#include "Engine.h"
#include "Game.h"

irr::gui::IGUIImage* img;

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