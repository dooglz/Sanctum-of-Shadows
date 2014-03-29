#pragma once
#include <irrlicht.h>

class Pathfinder{

private:
	Pathfinder();
	~Pathfinder();
public:
	static irr::core::vector3df getDarkLocation();
	static irr::core::vector3df getLocationWithinTile(irr::core::vector2d<int> coord);

};