#pragma once
#include <irrlicht.h>
#include "Character.h"

class Player:public Character{
private:
	irr::scene::ICameraSceneNode* _camera;
public:
	Player(){};
	~Player(){};
	bool loadContent();
	void unloadContent();
	void update(float delta);
	irr::scene::ICameraSceneNode* getCamera() { return _camera; }
	void intitalise(irr::core::vector3df position);
};
