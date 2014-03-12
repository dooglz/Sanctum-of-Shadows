#pragma once
#include "Game.h"
#include "Engine.h"
#include "Player.h"

class SanctumOfShadows:public Game{
private:
	void reset();
public:
	SanctumOfShadows(){
		_gameTitle = L"SanctumOfShadows";
		_resolution  = irr::core::dimension2d<irr::u32>(1280, 720);
	};
	static Player* player;
	~SanctumOfShadows(){};
	bool init();
	bool update(float delta);
};