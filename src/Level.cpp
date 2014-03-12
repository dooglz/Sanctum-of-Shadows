#include "Engine.h"
#include "Level.h"
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
	irr::video::ITexture* targetTexture = GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_radius.png");

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
	
	loadGeo();
	return true;
}

void Level::update(float delta)
{


}

void Level::loadGeo()
{
	//base cubes
	std::array<irr::core::vector3df, 26> positions = {
		irr::core::vector3df(-1000,0,-1000), irr::core::vector3df(100.0f,400.0f,100.0f),
		irr::core::vector3df(-1000,0,1000), irr::core::vector3df(100.0f,400.0f,100.0f),
		irr::core::vector3df(1000,0,-1000), irr::core::vector3df(100.0f,400.0f,100.0f),
		irr::core::vector3df(1000,0,1000), irr::core::vector3df(100.0f,400.0f,100.0f),

		irr::core::vector3df(0,0,-1500), irr::core::vector3df(1000.0f,400.0f,100.0f),
		irr::core::vector3df(0,0,1500), irr::core::vector3df(1000.0f,400.0f,100.0f),
		irr::core::vector3df(1500,0,0), irr::core::vector3df(100.0f,400.0f,1000.0f),
		irr::core::vector3df(-1500,0,0), irr::core::vector3df(100.0f,400.0f,1000.0f),

		irr::core::vector3df(-1000,0,0), irr::core::vector3df(30.0f,200.0f,500.0f),
		irr::core::vector3df(-800,0,0), irr::core::vector3df(30.0f,200.0f,400.0f),
		irr::core::vector3df(-600,0,0), irr::core::vector3df(30.0f,200.0f,300.0f),
		irr::core::vector3df(-400,0,0), irr::core::vector3df(30.0f,200.0f,200.0f),
		irr::core::vector3df(-200,0,0), irr::core::vector3df(30.0f,200.0f,100.0f)

	};
	for (unsigned int i=0; i< positions.size(); i+=2) {
		irr::scene::ISceneNode* geoNode = GameEngine::engine.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
		geoNode->setPosition(positions[i]);
		geoNode->setScale(positions[i+1]);
		geoNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
		geoNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
		geoNode->setMaterialTexture(0,GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_spiral.jpg"));
	}

	std::array<irr::core::vector3df, 10> positions2 = {
		irr::core::vector3df(1000,-100,0), irr::core::vector3df(30.0f,200.0f,500.0f),
		irr::core::vector3df(800,-100,0), irr::core::vector3df(30.0f,200.0f,400.0f),
		irr::core::vector3df(600,-100,0), irr::core::vector3df(30.0f,200.0f,300.0f),
		irr::core::vector3df(400,-100,0), irr::core::vector3df(30.0f,200.0f,200.0f),
		irr::core::vector3df(200,-100,0), irr::core::vector3df(30.0f,200.0f,100.0f)
	};

	irr::scene::IAnimatedMesh* cube = GameEngine::engine.getDevice()->getSceneManager()->getMesh("models/cube1.obj");
	for (unsigned int i=0; i< positions2.size(); i+=2) {
		irr::scene::ISceneNode* geoNode = GameEngine::engine.getDevice()->getSceneManager()->addAnimatedMeshSceneNode(cube);
		geoNode->setPosition(positions2[i]);
		geoNode->setScale(positions2[i+1]);
		geoNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
		geoNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	}

	std::array<irr::core::vector3df, 5> positions3 = {
		irr::core::vector3df(0,0,-1000),
		irr::core::vector3df(0,0,-800),
		irr::core::vector3df(0,0,-600),
		irr::core::vector3df(0,0,-400),
		irr::core::vector3df(0,0,-200),
	};

	irr::scene::IAnimatedMesh* beacon = GameEngine::engine.getDevice()->getSceneManager()->getMesh("models/beacon.obj");
	for (unsigned int i=0; i< positions3.size(); i+=1) {
		irr::scene::ISceneNode* geoNode = GameEngine::engine.getDevice()->getSceneManager()->addAnimatedMeshSceneNode(beacon);
		geoNode->setPosition(positions3[i]);
		geoNode->setScale( irr::core::vector3df(15.0f,15.0f,15.0f));
		geoNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
		geoNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	}


	irr::scene::ISceneNode* geoNode = GameEngine::engine.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
		geoNode->setPosition(irr::core::vector3df(200,0,0));
		geoNode->setScale(irr::core::vector3df(200.0f,400.0f,30.0f));
		geoNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
		geoNode->setMaterialTexture(0,GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_spiral.jpg"));
	irr::scene::ISceneNodeAnimator* anim = GameEngine::engine.getDevice()->getSceneManager()->
		createFlyStraightAnimator(irr::core::vector3df(0,0,200),irr::core::vector3df(0,0,1000),6000.0f,true,true);
	geoNode->addAnimator(anim);
	//anim->drop();



}
