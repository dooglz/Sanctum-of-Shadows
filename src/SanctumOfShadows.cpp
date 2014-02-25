#include "SanctumOfShadows.h"

bool SanctumOfShadows::init(){
	std::wcout <<  _gameTitle << " Game code init" << std::endl;
	//
	if (!GameEngine::engine.loadContent()){
		return false;
	}
	irr::scene::ISceneManager* smgr = GameEngine::engine.getDevice()->getSceneManager();

	//Add a cube at origin, for bearings
	irr::scene::ISceneNode* originBox = smgr->addCubeSceneNode(1.0f);
	originBox->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	originBox->setMaterialTexture(0,GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_dev_check.png"));

	//load the level
	GameEngine::engine.getDevice()->getFileSystem()->addFileArchive("maps/map-20kdm2.pk3");
	irr::scene::IAnimatedMesh* mesh = smgr->getMesh("20kdm2.bsp");
    irr::scene::IMeshSceneNode* q3node = 0;
	irr::scene::ITriangleSelector* selector = 0;
    if (mesh)
	{
		q3node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
		if (q3node)
		{
			//Center map with world origin
			q3node->setPosition(irr::core::vector3df(-1200,-144,-1249));
			//Create a Triangle selector (AKA hitbox) made up of all the traingles in the map mesh 
			selector = smgr->createOctreeTriangleSelector(q3node->getMesh(), q3node, 128);
			//register the hitbox/selector to the node
			q3node->setTriangleSelector(selector);
			// We're not done with this selector yet, so don't drop it.
		}
	}

	//add fps camera
	irr::scene::ICameraSceneNode* camera = GameEngine::engine.getDevice()->getSceneManager()->addCameraSceneNodeFPS();

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


	return true;
}

bool SanctumOfShadows::update(float delta){

	//TODO, move some of this to baseclass
	if(GameEngine::handler.keyDown(irr::KEY_F1)){
		GameEngine::engine.debug();
	}

	return true;
}

void SanctumOfShadows::reset(){

}
