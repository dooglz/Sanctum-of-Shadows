#pragma once
#include "Entity.h"
#include <array>
#include <ctime>
class Level: public GameEngine::Entity{
private:
	irr::scene::ITriangleSelector* _selector;
	void placeBeacons();
	void generateLevel();
	//level gen stuff
	static const unsigned int _gridSize = 79;	//Has to be an odd number
	static const unsigned int _darkPadding = 1;	//amount of dark tiles lining the edge
	static const unsigned int _maxObstacles = 2; // Max obstacles to spawn around a beacon
	//Init grid, add border
	static const enum tile {EMPTY,BADLANDS,BEACON,OBSTACLE};
	static std::array<std::array<tile,_gridSize>, _gridSize> _grid;

public:
	Level() :Entity(-1,0,"Level"){}
	~Level(){};
	void intitalise();
	bool loadContent();
	void unloadContent(){};
	void update(float delta);
	irr::scene::ITriangleSelector* getSelector(){
		return _selector;
	}
};