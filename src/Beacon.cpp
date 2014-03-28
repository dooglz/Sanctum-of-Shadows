#include "Beacon.h"
/*
Beacon::Beacon(GameState* parentState, const irr::core::vector3df& position) : GameEngine::StaticPhysicalEntity(parentState,0,"Beacon")
{
	bool particles = true;
	bool flame = true;
	_alive = true;

	//scene node
	loadContent();
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	_node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	irr::core::vector3df scale = irr::core::vector3df(15.0f,15.0f,15.0f);
	_node->setScale(scale);
	_node->setPosition(position);
	
	// create light
	_light = GameEngine::engine.getDevice()->getSceneManager()->addLightSceneNode(
		_node, irr::core::vector3df(0,6.0f,0),			//Parent and offset
		irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f),	//Colour
		(irr::f32)_lightRange		//Radius
	);	

	_rigidBody = createBoundingBoxRB( _node, irr::core::vector3df(0,scale.Y*0.5f*_node->getTransformedBoundingBox().getExtent().Y,0) );
	GameEngine::Physics::world->addRigidBody(_rigidBody);

	// create a particle system
	float particleRadius = _lightRange / (2.0f*scale.X);
	irr::scene::IParticleSystemSceneNode* ps = GameEngine::engine.getDevice()->getSceneManager()->addParticleSystemSceneNode(false,_node);
	irr::scene::IParticleEmitter* em = ps->createRingEmitter(
		irr::core::vector3df(0,0,0),
		particleRadius / 2.0f,					//Ring Radius
		particleRadius,							//Ring thickness
		irr::core::vector3df(0.0f,0.06f,0.0f),	//Direction
		3,										//Min particles per second
		80,										//Max particles per second
		irr::video::SColor(0,128,128,128),      //Darkest color
		irr::video::SColor(0,255,255,255),      //Brightest color
		800,		//Min Age
		2000,		//Max Age
		0,			//Angle			
		irr::core::dimension2df(2.0f,2.0f),     // Min size
		irr::core::dimension2df(10.f,10.f)		// max size
	);        

	ps->setEmitter(em); // this grabs the emitter
	em->drop(); // so we can drop it here without deleting it

	irr::scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();
	ps->addAffector(paf); // same goes for the affector
	paf->drop();

	ps->setPosition(irr::core::vector3df(0,3.0f,0));
	ps->setScale(irr::core::vector3df(1,1,1));
	ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/particlewhite.bmp"));
	ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	_effects.push_back(ps);

	//Flame Effect
	irr::scene::IVolumeLightSceneNode * n = GameEngine::engine.getDevice()->getSceneManager()->addVolumeLightSceneNode(_node, -1,
			32,                              // Subdivisions on U axis
			32,                              // Subdivisions on V axis
			irr::video::SColor(0, 255, 255, 255), // foot color
			irr::video::SColor(0, 0, 0, 0));      // tail color
	if (n)
	{
		n->setScale(irr::core::vector3df(3.0f, 5.0f, 3.0f));
		n->setPosition(irr::core::vector3df(0,3.0f,0));

		// load textures for animation
		irr::core::array<irr::video::ITexture*> textures;
		for (irr::s32 g=7; g > 0; --g)
		{
			irr::core::stringc tmp;
			tmp = "textures/portal";
			tmp += g;
			tmp += ".bmp";
			irr::video::ITexture* t = GameEngine::engine.getDevice()->getVideoDriver()->getTexture( tmp.c_str() );
			textures.push_back(t);
		}

		// create texture animator
		irr::scene::ISceneNodeAnimator* glow = GameEngine::engine.getDevice()->getSceneManager()->createTextureAnimator(textures, 120);

		// add the animator
		n->addAnimator(glow);

		// drop the animator because it was created with a create() function
		glow->drop();
		_effects.push_back(n);
	}

	//set beacon to be unlit innitially
	light(false);
}


// Toggle state, lights and effects.
void Beacon::light(bool onOff)
{
	_isLit = onOff;
	//change radius of main Light
	if(_isLit)
	{
		_light->setRadius((irr::f32)_lightRange);
	}
	else
	{
		_light->setRadius(0.25f * _lightRange);
	}
	//toggle all effects
	for(auto& e : _effects) {
		e->setVisible(_isLit);
	}
}


bool Beacon::loadContent()
{
	irr::scene::IAnimatedMesh* beaconModel = GameEngine::engine.getDevice()->getSceneManager()->getMesh("models/beacon.obj");
	if (!beaconModel)
	{
		std::cerr << "Error loading beaconModel" << std::endl;
		return false;
	}
	_node = GameEngine::engine.getDevice()->getSceneManager()->addAnimatedMeshSceneNode(beaconModel);
	return true;
}

// Check player location, turn on, Heal player.
void Beacon::update(float delta)
{
	float distanceToPlayer = (SanctumOfShadows::player->getNode()->getPosition() - _node->getPosition()).getLength();
	if(_isLit)
	{
		if(distanceToPlayer < _healingRange)
		{
			float a = SanctumOfShadows::player->getHealth();
			if( a < 150.0f)
			{
				//player getting healed by beacon
				SanctumOfShadows::player->setHealth( a + (5.0f * delta));
			}
		}
	}
	else
	{
		if(distanceToPlayer < _healingRange)
		{
			light(true);
		}
	}
}

void Beacon::handleMessage(const GameEngine::Message& message)
{
	if(message.message == "light")
	{
		_isLit = true;
	}
}

void Beacon::intitalise(){
	_alive = true;
	light(false);

}
*/