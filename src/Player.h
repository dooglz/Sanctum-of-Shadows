#pragma once
#include <irrlicht.h>
#include "PhysicalEntity.h"
#include "Box.h"

class Player{
private:
	GameEngine::PhysicalEntity* _physicsMesh;
	irr::scene::ICameraSceneNode* _camera;
public:
	Player(){};
	~Player(){};
	void intitalise(irr::core::vector3df position);
	bool loadContent();
	void unloadContent();
	void update(float delta);
};

/*
#pragma once
#include "Entity.h"

class Player: public GameEngine::Entity{
private:
	irr::scene::ITriangleSelector* _selector;
public:
	Player() :Entity(-1,0,"Player"){}
	~Player(){};
	void intitalise();
	bool loadContent();
	void unloadContent(){};
	void update(float delta);
};
*/