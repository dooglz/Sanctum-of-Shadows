#pragma once
#include "Main_Scene.h"

Main_Scene::Main_Scene():GameState("main")
{
	std::cout << "Main_Scene constructor" << std::endl;
}

Main_Scene::~Main_Scene()
{
	std::cout << "Main_Scene destructor" << std::endl;
}

bool Main_Scene::loadContent()
{
	std::cout << "Main_Scene loadContent" << std::endl;
	return true;
}

void Main_Scene::initialize()
{
	std::cout << "Main_Scene initialize" << std::endl;
}

void Main_Scene::flush()
{
	std::cout << "Main_Scene Flush" << std::endl;
}

void Main_Scene::update(float delta)
{
	
}

void Main_Scene::render()
{
	
}