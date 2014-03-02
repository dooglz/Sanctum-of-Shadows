#include "Engine.h"
#include "Level.h"
#include <iostream>
#include "Box.h"

void Level::intitalise()
{
	_selector = 0;
}

bool Level::loadContent()
{
	//Box* floor = new Box(btVector3(0,0,0),irr::core::vector3df(1000.0f,1.0f,1000.0f),0.0f);
	
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0.0, 1.0, 0.0), 1.0);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),btVector3(0,-1,0)));

	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0.0, 0.0, 0.0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	GameEngine::Physics::world->addRigidBody(groundRigidBody,GameEngine::Physics::E_Static,GameEngine::Physics::E_StaticGroup);

	irr::scene::IAnimatedMesh* am = GameEngine::engine.getDevice()->getSceneManager()->addHillPlaneMesh("plane", irr::core::dimension2df(1000,1000), irr::core::dimension2du(1,1));
	if (am)
	{
	  irr::scene::IMeshSceneNode* msn = GameEngine::engine.getDevice()->getSceneManager()->addMeshSceneNode(am->getMesh(0));
	  msn->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_check.png"));
	  msn->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}

	//GameEngine::engine.getDevice()->getFileSystem()->addFileArchive("maps/map-20kdm2.pk3");
	//irr::scene::IAnimatedMesh* mesh = GameEngine::engine.getDevice()->getSceneManager()->getMesh("20kdm2.bsp");
	//irr::scene::IMeshSceneNode* mesh = GameEngine::engine.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	//mesh->setScale(irr::core::vector3df(1000.0f,0,1000.0f));
	//mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	/*
	irr::scene::IMeshSceneNode* q3node = 0;
	irr::scene::ITriangleSelector* selector = 0;
    if (mesh)
	{
		//GameEngine::meshManager.analyseI(mesh);
		q3node = GameEngine::engine.getDevice()->getSceneManager()->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
		if (q3node)
		{
			//Center map with world origin
			q3node->setPosition(irr::core::vector3df(-1400,-144,-1349));
			q3node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
			q3node->setMaterialType(irr::video::EMT_LIGHTMAP_LIGHTING_M4);

			//Create a Triangle selector (AKA hitbox) made up of all the traingles in the map mesh 
			_selector = GameEngine::engine.getDevice()->getSceneManager()->createOctreeTriangleSelector(q3node->getMesh(), q3node, 128);
			//register the hitbox/selector to the node
			q3node->setTriangleSelector(selector);
			// We're not done with this selector yet, so don't drop it.
		}
	}
	*/

	return true;
}

void Level::update(float delta)
{


}
