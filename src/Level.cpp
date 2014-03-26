#include "Engine.h"
#include "Level.h"
#include "Beacon.h"
#include "Obstacle.h"
#include <iostream>
#include "Box.h"
#include <array>

std::array<std::array<Level::tile,Level::_gridSize>, Level::_gridSize> Level::_grid;

// Generate and Create level.
void Level::intitalise()
{	
	//Bullet floor plane
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0.0, 1.0, 0.0), 1.0);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0.0, 0.0, 0.0));
	_groundPlaneRB = new btRigidBody(groundRigidBodyCI);
	GameEngine::Physics::world->addRigidBody(_groundPlaneRB,GameEngine::Physics::E_Static,GameEngine::Physics::E_StaticGroup);

	//generate
	srand((int)time(0));
	generateLevel();

	//Create
	createLevel();

	//Populate
	//placeBeacons();
}

// Place beacons in the level.
void Level::placeBeacons()
{
	std::array<irr::core::vector3df, 5> positions = {
		irr::core::vector3df(0,0,800),
		irr::core::vector3df(0,0,-800),
		irr::core::vector3df(800,0,0),
		irr::core::vector3df(-800,0,0),
		irr::core::vector3df(0,0,0),
	};

	for (unsigned int i=0; i< positions.size(); i++) {
		new Beacon(positions[i]);
	}
}

// Spawn the entities and geometry as laid out by generateLevel().
void Level::createLevel()
{
	GameEngine::engine.getDevice()->getVideoDriver()->setFog(irr::video::SColor(0,0,0,0), irr::video::EFT_FOG_LINEAR, 250, 1000, .003f, true, false);	

	float tileSize = (float)_tileSize;
	irr::video::ITexture* cobbleTex = GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_cobble_1024.jpg");
	irr::video::ITexture* darkTex = GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_cobble_d_1024.jpg");
	irr::video::ITexture* lightTex = GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_cobble_l_1024.jpg");
	irr::scene::IAnimatedMesh* planeMesh = GameEngine::engine.getDevice()->getSceneManager()->addHillPlaneMesh("floormesh", irr::core::dimension2df(tileSize,tileSize), irr::core::dimension2du(1,1));
	irr::scene::IAnimatedMesh* cubeMesh = GameEngine::engine.getDevice()->getSceneManager()->getMesh("models/cube1.obj");
	
	std::array<irr::scene::IMeshSceneNode*, (_gridSize*_gridSize)> floorTiles;

	unsigned int a =0;
	float startingPos = (-1.0f * (0.5f*(tileSize * _gridSize))) +(0.5f*tileSize);

	for(unsigned int col = 0; col < _grid.size(); col ++)
	{
		for(unsigned int row = 0; row < _grid[col].size(); row ++)
		{
			irr::core::vector3df origin = irr::core::vector3df(startingPos + (col*tileSize),0,startingPos + (row*tileSize));

			irr::scene::IMeshSceneNode* node;
			node = GameEngine::engine.getDevice()->getSceneManager()->addMeshSceneNode(planeMesh->getMesh(0));

			//node->getMaterial(0).SpecularColor.set(0,0,0,0);
			//node->getMaterial(0).EmissiveColor.set(255,0,0,0);
			
			node->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
			//node->setMaterialType(irr::video::EMT_SOLID);
			node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
			node->setMaterialFlag(irr::video::EMF_LIGHTING, true);

			//node->setScale(irr::core::vector3df(500.0f,2.0f,500.0f));
			node->setPosition(origin);
			

			if(_grid[col][row] == BEACON)
			{
				node->setMaterialTexture(0, lightTex);
				new Beacon(origin);
			}
			else if(_grid[col][row] == OBSTACLE)
			{
				new Obstacle(origin,irr::core::vector3df(tileSize,tileSize,tileSize));
				node->setMaterialTexture(0, cobbleTex);
			}
			else if(_grid[col][row] == EMPTY)
			{
				node->setMaterialTexture(0, cobbleTex);
			}
			else
			{
				node->setMaterialTexture(0, darkTex);
			}
			floorTiles[a] = node;
			a++;
		}
	}
}

// Procedurally generate the level, populates _grid.
void Level::generateLevel()
{
	int pass = 0;
	bool full = false;
	bool done = false;
	//saves redundant array lookups within the loop
	tile curentTile;
	for(unsigned int col = 0; col < _grid.size(); col ++)
	{
		for(unsigned int row = 0; row < _grid[col].size(); row ++)
		{
			if(col < _darkPadding || col == (_gridSize - _darkPadding) || row < _darkPadding || row == (_gridSize - _darkPadding))
			{
				_grid[col][row] = BADLANDS;
			}
			else if(row == col && col == ((_gridSize-1)/2))
			{
				_grid[col][row] = BEACON;
			}
			else
			{
				_grid[col][row] = EMPTY;
			}
		}
	}

	int beacons = 0;
	int obstacles = 0;
	int spaces = 0;

	//Beacons
	for(unsigned int col = 0; col < _grid.size(); col ++)
	{
		for(unsigned int row = 0; row < _grid[col].size(); row ++)
		{
			curentTile = _grid[col][row];
			//We can't go out of range due to padding.
			if(curentTile == EMPTY)
			{
				if(_grid[col - 1][row - 1] != BEACON && _grid[col - 1][row] != BEACON && _grid[col - 1][row + 1] != BEACON
					&& _grid[col][row -1] != BEACON && _grid[col][row +1] != BEACON
					&& _grid[col + 1][row -1] != BEACON && _grid[col + 1][row] != BEACON &&  _grid[col + 1][row + 1] != BEACON)
				{
					//No beacons in surrounding area
					if (rand() % 100 < _beaconPercent) {
						_grid[col][row] = BEACON;
						beacons++;
					}
				}
			}
		}
	}

	//Obstacles
	for(unsigned int col = 0; col < _grid.size(); col ++)
	{
		for(unsigned int row = 0; row < _grid[col].size(); row ++)
		{
			curentTile = _grid[col][row];
			//We can't go out of range due to padding.
			if(curentTile == EMPTY)
			{
				if(_grid[col - 1][row - 1] != OBSTACLE && _grid[col - 1][row] != OBSTACLE && _grid[col - 1][row + 1] != OBSTACLE
					&& _grid[col][row -1] != OBSTACLE && _grid[col][row +1] != OBSTACLE
					&& _grid[col + 1][row -1] != OBSTACLE && _grid[col + 1][row] != OBSTACLE &&  _grid[col + 1][row + 1] != OBSTACLE)
				{
					//No beacons in surrounding area
					if (rand() % 100 < _obstaclePercent) {
						_grid[col][row] = OBSTACLE;
						obstacles++;
					}
				}
			}
		}
	}

	
	//print
	for(unsigned int col = 0; col < _grid.size(); col ++)
	{
		for(unsigned int row = 0; row < _grid[col].size(); row ++)
		{
			if(_grid[col][row] == BADLANDS){
				std::cout << char(178);
			}else if(_grid[col][row] == EMPTY){
				std::cout << char(176);
			}else if(_grid[col][row] == OBSTACLE){
				std::cout << char(254);
			}
			else{
				std::cout << char(233);
			}
		}
		std::cout << std::endl;
	}

}

// Load level meshes
bool Level::loadContent(){
	//TODO
	return true;
}
