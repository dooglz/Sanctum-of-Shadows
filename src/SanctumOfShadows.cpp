#include "SanctumOfShadows.h"
#include "Box.h"

#include <btBulletDynamicsCommon.h>


irr::scene::ICameraSceneNode* camera;
irr::scene::ICameraSceneNode* Flycamera;
irr::scene::ICameraSceneNode* Menucamera;
bool _flying;

bool SanctumOfShadows::init(){
	std::wcout <<  _gameTitle << " Game code init" << std::endl;
	//
	if (!GameEngine::engine.loadContent()){
		return false;
	}
	irr::scene::ISceneManager* smgr = GameEngine::engine.getDevice()->getSceneManager();

	//Add a cube at origin, for bearings
	irr::scene::IAnimatedMesh* cube = smgr->getMesh("models/cube1.obj");
	if (!cube)
	{
		std::cerr << "Error loading Mesh" << std::endl;
		return false;
	}
	
	irr::scene::ISceneNode* originBox = smgr->addMeshSceneNode(cube);
	originBox->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	originBox->setScale(irr::core::vector3df(10,10,10));
	//load the level
	GameEngine::engine.getDevice()->getFileSystem()->addFileArchive("maps/map-20kdm2.pk3");
	irr::scene::IAnimatedMesh* mesh = smgr->getMesh("20kdm2.bsp");
    irr::scene::IMeshSceneNode* q3node = 0;
	irr::scene::ITriangleSelector* selector = 0;
    if (mesh)
	{
		//GameEngine::meshManager.analyseI(mesh);
		q3node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
		if (q3node)
		{
			//Center map with world origin
			q3node->setPosition(irr::core::vector3df(-1400,-144,-1349));
			//q3node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
			//q3node->setMaterialType(irr::video::EMT_LIGHTMAP_LIGHTING_M4);

			//Create a Triangle selector (AKA hitbox) made up of all the traingles in the map mesh 
			selector = smgr->createOctreeTriangleSelector(q3node->getMesh(), q3node, 128);
			//register the hitbox/selector to the node
			q3node->setTriangleSelector(selector);
			// We're not done with this selector yet, so don't drop it.
		}
	}

	//add fps camera

	camera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNodeFPS();
	Flycamera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNodeFPS();
	Menucamera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNode(0,irr::core::vector3df(0,0,223),irr::core::vector3df(0,0,0));

	//setup camera to world collision
	if (selector)
    {
		irr::scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
            selector, camera, 
			//Camera/Player size, Eplisoid, x50 hight, x30 radius
			irr::core::vector3df(30,50,30),
			//Gravity affecting player
            irr::core::vector3df(0,-10,0), 
			//translate hitbox down, so camera is at eye level rather than centered.
			irr::core::vector3df(0,30,0)
		);
		// As soon as we're done with the selector, drop it.
        selector->drop();
        camera->addAnimator(anim);
		// And likewise, drop the animator when we're done referring to it.
        anim->drop();
    }

	// create light
	irr::scene::ISceneNode* node = 0;
	node = smgr->addLightSceneNode(0, irr::core::vector3df(0,0,0), irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 1000.0f);
	irr::scene::ISceneNodeAnimator* anim = 0;
	anim = smgr->createFlyCircleAnimator (irr::core::vector3df(0,0,0),200.0f);
	node->addAnimator(anim);
	anim->drop();

	// attach billboard to light
	node = smgr->addBillboardSceneNode(node, irr::core::dimension2d<irr::f32>(50, 50));
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	node->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	node->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/particlewhite.bmp"));

	//Text physics box
	new Box(btVector3(0,-70.0f,0),irr::core::vector3df(150.0f,1.0f,150.0f),0.0f);
	new Box(btVector3(0,-120.0f,0),irr::core::vector3df(400.0f,1.0f,400.0f),0.0f);
	//

	irr::scene::ISceneNode* multiBox = smgr->addMeshSceneNode(cube,0,-1,irr::core::vector3df(0,-30.0f,0));
	multiBox->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	multiBox->setScale(irr::core::vector3df(10,10,10));

	//GameEngine::meshManager.analyse(cube,true);
	


	//Rigid body
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(0,0,0));
	btDefaultMotionState* motionstate = new btDefaultMotionState(transform);

	//setup shape
	btCollisionShape* shape = GameEngine::meshManager.convertToBulletTriangleMesh(cube);

	//calc intertia, based on mass and shape
	btVector3 localInertia(0,0,0);
	//shape->calculateLocalInertia(1.0f,localInertia);

	//create the RB
	btRigidBody* _rigidBody = new btRigidBody(0,0,shape,localInertia);
	//add to world
	GameEngine::Physics::world->addRigidBody(_rigidBody);


	return true;
}

bool a;
bool SanctumOfShadows::update(float delta){

	//TODO, move some of this to baseclass
	if(GameEngine::handler.keyDown(irr::KEY_F1)){
		GameEngine::engine.debug();
	}
	if(GameEngine::handler.keyDown(irr::KEY_F2)){
		GameEngine::engine.getDevice()->getSceneManager()->setActiveCamera(camera);
	}
	if(GameEngine::handler.keyDown(irr::KEY_F3)){
		GameEngine::engine.getDevice()->getSceneManager()->setActiveCamera(Flycamera);
	}
	if(GameEngine::handler.keyDown(irr::KEY_F4)){
		GameEngine::engine.getDevice()->getSceneManager()->setActiveCamera(Menucamera);
	}
	if(GameEngine::handler.keyDown(irr::KEY_F5)){
		new Box(btVector3(-75.0f + ((((float) rand()) / ((float) RAND_MAX))*150.0f),0,-75.0f + ((((float) rand()) / ((float) RAND_MAX))*150.0f)),irr::core::vector3df(10.0f,10.0f,10.0f),10.0f);
	}
	if(!a && GameEngine::handler.keyDown(irr::KEY_F6)){
		new Box(btVector3(0,30,0),irr::core::vector3df(10.0f,10.0f,10.0f),10.0f);
		a = true;
	}

	return true;
}

void SanctumOfShadows::reset(){

}
