#include "Level.h"
#include <ctime>

std::array<std::array<Level::tile,Level::_gridSize>, Level::_gridSize> Level::_grid;

Level::Level(GameEngine::GameState* parentState):Entity(parentState,0,"Level")
{
}

// Generate and Create level.
void Level::intitalise()
{	
	//Bullet floor plane
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0.0, 1.0, 0.0), 1.0);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0.0, 0.0, 0.0));
	_groundPlaneRB = new btRigidBody(groundRigidBodyCI);
	GameEngine::Physics::world->addRigidBody(_groundPlaneRB,GameEngine::Physics::E_Static,GameEngine::Physics::E_StaticGroup);

	_isLit = true;

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
		new Beacon(_parentstate,positions[i]);
	}
}

// Spawn the entities and geometry as laid out by generateLevel().
void Level::createLevel()
{
	//fog
	GameEngine::engine.getDevice()->getVideoDriver()->setFog(irr::video::SColor(0,0,0,0), irr::video::EFT_FOG_LINEAR, 250, 1000, .003f, true, false);	

	float tileSize = (float)_tileSize;
	irr::video::ITexture* cobbleTex = GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_cobble2_1024.jpg");
	irr::video::ITexture* darkTex = GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_cobble_d_1024.jpg");
	irr::video::ITexture* lightTex = GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_cobble_l_1024.jpg");

	//Normals are saved into meshdata once applied, So we need two meshes for the two different textures+normals.
	irr::video::ITexture* normalMap = GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_cobble_1024_NRM.jpg");
	irr::video::ITexture* normalMap2 = GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_cobble2_1024_NRM.jpg");

	irr::scene::IAnimatedMesh* planeMesh = GameEngine::engine.getDevice()->getSceneManager()->addHillPlaneMesh("floormesh", irr::core::dimension2df(tileSize/4,tileSize/4), irr::core::dimension2du(4,4));
	irr::scene::IAnimatedMesh* planeMesh2 = GameEngine::engine.getDevice()->getSceneManager()->addHillPlaneMesh("floormesh2", irr::core::dimension2df(tileSize/4,tileSize/4), irr::core::dimension2du(4,4));
	irr::scene::IMesh* tangentMesh = GameEngine::engine.getDevice()->getSceneManager()->getMeshManipulator()->createMeshWithTangents(planeMesh->getMesh(0));
	irr::scene::IMesh* tangentMesh2 = GameEngine::engine.getDevice()->getSceneManager()->getMeshManipulator()->createMeshWithTangents(planeMesh2->getMesh(0));

	unsigned int a =0;
	float startingPos = (-1.0f * (0.5f*(tileSize * _gridSize))) +(0.5f*tileSize);

	for(unsigned int col = 0; col < _grid.size(); col ++)
	{
		for(unsigned int row = 0; row < _grid[col].size(); row ++)
		{

			irr::core::vector3df origin = irr::core::vector3df(startingPos + (col*tileSize),0,startingPos + (row*tileSize));

			if(_grid[col][row] == OBSTACLE)
			{
				_obstacles.push_back( new Obstacle(_parentstate, origin,irr::core::vector3df(tileSize,tileSize,tileSize)) );
			}
			else
			{
				irr::scene::IMeshSceneNode* node;

				if(_grid[col][row] == BEACON)
				{
					node = GameEngine::engine.getDevice()->getSceneManager()->addMeshSceneNode(tangentMesh);
					node->setMaterialTexture(0, lightTex);
					node->setMaterialTexture(1, normalMap);
					_beacons.push_back( new Beacon(_parentstate,origin) );
				}
				else if(_grid[col][row] == EMPTY)
				{
					node = GameEngine::engine.getDevice()->getSceneManager()->addMeshSceneNode(tangentMesh2);
					node->setMaterialTexture(0, cobbleTex);
					node->setMaterialTexture(1, normalMap2);
				}
				else
				{
					node = GameEngine::engine.getDevice()->getSceneManager()->addMeshSceneNode(tangentMesh);
					node->setMaterialTexture(0, darkTex);
				}

				//Normal map parameters
				node->getMaterial(1).MaterialTypeParam = 1.f / 64.f;
				node->getMaterial(1).SpecularColor.set(0,0,0,0);
				node->getMaterial(1).EmissiveColor.set(255,0,0,0);
			
				node->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
				node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
				node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
				node->setMaterialType(irr::video::EMT_NORMAL_MAP_SOLID);

				node->setPosition(origin);

				_floorTiles.push_back(node);
			}

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

// Sets EMF_LIGHTING on all level nodes.
void Level::toggleLighting(bool a)
{
	_isLit = a;
	for (irr::scene::IMeshSceneNode* i : _floorTiles ) 
	{
		i->setMaterialFlag(irr::video::EMF_LIGHTING, a);
		i->setMaterialFlag(irr::video::EMF_FOG_ENABLE, a);
		if(!a)
		{
			i->setMaterialType(irr::video::EMT_SOLID);
		}
		else
		{
			i->setMaterialType(irr::video::EMT_NORMAL_MAP_SOLID);
		}
	}
	for (Obstacle* j : _obstacles ) 
	{
		j->getNode()->setMaterialFlag(irr::video::EMF_LIGHTING, a);
		j->getNode()->setMaterialFlag(irr::video::EMF_FOG_ENABLE, a);
	}
}