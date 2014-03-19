#include "Engine.h"
#include "Level.h"
#include "Beacon.h"
#include <iostream>
#include "Box.h"
#include <array>
void Level::intitalise()
{
	_selector = 0;
}

bool Level::loadContent()
{

	bool loadLevel = false;
	bool lightedFloor = false;
	//Box* floor = new Box(btVector3(0,0,0),irr::core::vector3df(1000.0f,1.0f,1000.0f),0.0f);
	
	//Bullet floor plane
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0.0, 1.0, 0.0), 1.0);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0.0, 0.0, 0.0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	GameEngine::Physics::world->addRigidBody(groundRigidBody,GameEngine::Physics::E_Static,GameEngine::Physics::E_StaticGroup);
	
	//Floor plane render node
	irr::video::ITexture* targetTexture = GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_cobble.jpg");

	irr::scene::IMeshSceneNode* floorNode;
	if(!lightedFloor)
	{
		irr::scene::IAnimatedMesh*  floorMesh = GameEngine::engine.getDevice()->getSceneManager()->addHillPlaneMesh("plane", irr::core::dimension2df(250,250), irr::core::dimension2du(16,16));
		floorNode = GameEngine::engine.getDevice()->getSceneManager()->addMeshSceneNode(floorMesh->getMesh(0));
		floorNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	}
	else
	{
		floorNode = GameEngine::engine.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
		floorNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
		floorNode->setScale(irr::core::vector3df(3000.0f,1,3000.0f));
	}
	
	floorNode->setMaterialTexture(0, targetTexture);

	//Quake Node
	if(loadLevel)
	{
		GameEngine::engine.getDevice()->getFileSystem()->addFileArchive("maps/map-20kdm2.pk3");
		irr::scene::IAnimatedMesh* quakeMesh = GameEngine::engine.getDevice()->getSceneManager()->getMesh("20kdm2.bsp");
		//mesh->setScale(irr::core::vector3df(1000.0f,0,1000.0f));
		quakeMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
		irr::scene::IMeshSceneNode* q3node = 0;
		irr::scene::ITriangleSelector* selector = 0;
		//GameEngine::meshManager.analyseI(mesh);
		q3node = GameEngine::engine.getDevice()->getSceneManager()->addOctreeSceneNode(quakeMesh->getMesh(0), 0, -1, 1024);
		//Center map with world origin
		q3node->setPosition(irr::core::vector3df(-1400,-62,-1349));
		q3node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
		q3node->setMaterialType(irr::video::EMT_LIGHTMAP_LIGHTING_M4);
		//Create a Triangle selector (AKA hitbox) made up of all the traingles in the map mesh 
		_selector = GameEngine::engine.getDevice()->getSceneManager()->createOctreeTriangleSelector(q3node->getMesh(), q3node, 128);
		//register the hitbox/selector to the node
		q3node->setTriangleSelector(selector);
		// We're not done with this selector yet, so don't drop it.
	}
	
	placeBeacons();
	return true;
}

void Level::update(float delta)
{


}
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
