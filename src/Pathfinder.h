#pragma once
#include "Level.h"
#include <irrlicht.h>

class Pathfinder{

private:
	Pathfinder();
	~Pathfinder();
public:
	static irr::core::vector3df getDarkLocation(){
		return irr::core::vector3df(0,0,0);
	}

};