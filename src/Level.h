#pragma once
#include "Entity.h"

class Level: public GameEngine::Entity{
private:
	irr::scene::ITriangleSelector* _selector;
public:
	Level() :Entity(-1,0,"Level"){}
	Level(irr::scene::IAnimatedMeshSceneNode* node) : Entity(0,node){}
	~Level(){};
	void intitalise();
	bool loadContent();
	void unloadContent(){};
	void update(float delta);
	irr::scene::ITriangleSelector* getSelector(){
		return _selector;
	}
};