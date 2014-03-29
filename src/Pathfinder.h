#pragma once
#include <irrlicht.h>

class Pathfinder{

private:
	Pathfinder();
	~Pathfinder();
public:
	static irr::core::vector3df getDarkLocation();

};