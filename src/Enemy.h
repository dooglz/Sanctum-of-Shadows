#pragma once
#include <irrlicht.h>
#include "Character.h"
#include "Player.h"

class Enemy:public Character{
private:
	//This will not be nessisary once these are true entities again.
	static Player* _player;
public:
	Enemy(irr::core::vector3df position);
	~Enemy(){};
	void intitalise(){};
	bool loadContent();
	void unloadContent();
	void update(float delta);
	static void setPlayerRef(Player* player){_player = player;}
};