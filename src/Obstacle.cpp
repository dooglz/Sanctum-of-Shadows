#include "Obstacle.h"

irr::scene::IAnimatedMesh* Obstacle::_mesh;
irr::video::ITexture* Obstacle::_texture;

Obstacle::Obstacle (const irr::core::vector3df& position, const irr::core::vector3df size) : GameEngine::StaticPhysicalEntity(-1,0, "Obstacle")
{
	//scene node
	loadContent();
	_node = GameEngine::engine.getDevice()->getSceneManager()->addMeshSceneNode(_mesh);
	_node->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	_node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	_node->setMaterialTexture(0, _texture);
	_node->setScale(size);
	_node->setPosition(position);
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

	if(_mesh){
		_mesh->drop();
	}
	if(_texture){
		_texture->drop();
	}
}