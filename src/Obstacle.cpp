#include "Obstacle.h"

irr::scene::IMesh* Obstacle::_mesh;
irr::video::ITexture* Obstacle::_texture;

Obstacle::Obstacle (const irr::core::vector3df& position, const irr::core::vector3df size) : GameEngine::StaticPhysicalEntity(-1,0, "Obstacle")
{

	//scene node
	loadContent();
	irr::scene::IMesh* m = GameEngine::engine.getDevice()->getSceneManager()->getMesh("models/cube1.obj");
	//GameEngine::engine.getDevice()->getSceneManager()->getMeshManipulator()->scale(m,size);
	//GameEngine::engine.getDevice()->getSceneManager()->getMeshManipulator()->recalculateNormals(m,0,0);
	GameEngine::engine.getDevice()->getSceneManager()->getMeshManipulator()->recalculateTangents(m,1,0,0);
	 //m = GameEngine::engine.getDevice()->getSceneManager()->getMeshManipulator()->createMeshWithTangents(m);

	_node = GameEngine::engine.getDevice()->getSceneManager()->addMeshSceneNode(m);
	//_node->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	_node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	_node->setMaterialTexture(0, _texture);
	_node->setPosition(position);

	_node->setMaterialType(irr::video::EMT_NORMAL_MAP_SOLID);
	_node->setMaterialTexture(1, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_cobble_1024_NRM.jpg"));
		_node->setScale(size);
		_node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	GameEngine::engine.getDevice()->getSceneManager()->getMeshManipulator()->recalculateNormals(m,true,false);
	//Collision
	_rigidBody = createBoundingBoxRB( _node, irr::core::vector3df(0,size.Y*0.5f*_node->getTransformedBoundingBox().getExtent().Y,0) );
	GameEngine::Physics::world->addRigidBody(_rigidBody);
}


bool Obstacle::loadContent()
{
	if(!_mesh)
	{
		_mesh = GameEngine::engine.getDevice()->getSceneManager()->getMesh("models/cube1.obj");
		if(!_mesh)
		{
			//TODO Crash bigtime here.
			std::cerr << "Error loading cube Model" << std::endl;
			return false;
		}else{
			_mesh = GameEngine::engine.getDevice()->getSceneManager()->getMeshManipulator()->createMeshWithTangents(_mesh);
		}
	}
	if(!_texture)
	{
		_texture = GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/tex_cobble_d_1024.jpg");
		if(!_texture)
		{
			//TODO Crash bigtime here.
			std::cerr << "Error loading Texture" << std::endl;
			return false;
		}
	}
	return true;
}

Obstacle::~Obstacle(){
	
	if(_mesh != nullptr ){
		_mesh->drop();
		_mesh = NULL;
	}
}