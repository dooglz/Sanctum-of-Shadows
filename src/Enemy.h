#pragma once
#include <irrlicht.h>
#include "Character.h"
#include "Player.h"

class Enemy:public Character{
private:
	//This will not be nessisary once these are true entities again.
	Player* _player;
public:
	Enemy(){};
	~Enemy(){};
	void intitalise(irr::core::vector3df position, Player* player);
	bool loadContent();
	void unloadContent();
	void update(float delta);
};