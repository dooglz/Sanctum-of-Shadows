#pragma once
#include <irrlicht.h>
#include "Character.h"

class Player:public Character{
private:
	irr::scene::ICameraSceneNode* _camera;
	irr::scene::ILightSceneNode* _Lanternlight;
	float _Lanternradius;
	bool LanternOn;
	float fuelLevel;
public:
	Player(irr::core::vector3df position);
	~Player(){};
	bool loadContent();
	void unloadContent();
	void update(float delta);
	irr::scene::ICameraSceneNode* getCamera() { return _camera; }
	void intitalise(){};
	void Player::handleMessage(const GameEngine::Message& message);
	void fuel(float delta);
	void setRadius(float value) { _Lanternradius = value;_Lanternlight->setRadius(_Lanternradius); }

};

