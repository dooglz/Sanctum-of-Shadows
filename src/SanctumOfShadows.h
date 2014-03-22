#pragma once
#include "Engine.h"
#include "Game.h"
#include "Player.h"

class SanctumOfShadows:public Game{

private:
	void reset();
	static bool _gameover;
public:
	SanctumOfShadows(){
		_gameTitle = L"SanctumOfShadows";
		_resolution  = irr::core::dimension2d<irr::u32>(1280, 720);
	};
	~SanctumOfShadows();
	static irr::scene::ISceneNode* DeadSpriteNode;
	static Player* player;
	bool init();
	bool update(float delta);
	static void GameOver();
	
};


