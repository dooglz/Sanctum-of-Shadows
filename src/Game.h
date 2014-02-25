#pragma once
#include <irrlicht.h>
#include <iostream>

class Game{
protected:
	std::wstring _gameTitle;
	irr::core::dimension2d<irr::u32> _resolution;
public:
	Game(){};
	virtual ~Game(){};
	virtual bool init() = 0;
	virtual bool update(float delta) = 0;
	std::wstring getGametitle(){
		return _gameTitle;
	}
	irr::core::dimension2d<irr::u32> getResolution(){
		return _resolution;
	}
};