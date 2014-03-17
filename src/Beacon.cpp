#include "Beacon.h"
#include "Engine.h"
#include "Player.h"
#include "SanctumOfShadows.h"

#include <iostream>

Beacon::Beacon(const irr::core::vector3df& position) : GameEngine::Entity(-1,0,"Beacon")
{
	bool particles = true;
	bool flame = false;
	_alive = true;

	//scene node
	loadContent();
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	_node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	irr::core::vector3df scale = irr::core::vector3df(15.0f,15.0f,15.0f);
	_node->setScale(scale);
	_node->setPosition(position);
	

	//set a healing range to heal the player
	_healingRange = 150;
	_lightRange = 500;
	
	// create light
	_light = GameEngine::engine.getDevice()->getSceneManager()->addLightSceneNode(
		_node, irr::core::vector3df(0,7.0f,0),			//Parent and offset
		irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f),	//Colour
		_lightRange);	//Radius
	
	//_light = GameEngine::engine.getDevice()->getSceneManager()->addLightSceneNode();
	
	/*
	irr::video::SLight& sl= _light->getLightData();
	sl.Type = irr::video::E_LIGHT_TYPE::ELT_SPOT;
	//rotate this, find out whats going on
	sl.Direction = irr::core::vector3df(1,-1,0);
	sl.DiffuseColor = irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f);
	sl.AmbientColor = irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f);
	sl.SpecularColor = irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f);
	sl.InnerCone = 60.0f;
	sl.OuterCone = 90.0f;
	sl.Falloff =  1000.0f;
	_light->setPosition(irr::core::vector3df(0,200.0f,0));
	

	// attach billboard sprite to light
	irr::scene::ISceneNode* LightSpriteNode = GameEngine::engine.getDevice()->getSceneManager()->addBillboardSceneNode(_light, irr::core::dimension2d<irr::f32>(50, 50));
	LightSpriteNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	LightSpriteNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	LightSpriteNode->setMaterialTexture(0, GameEngine::engine.getDevice()->getVideoDriver()->getTexture("textures/particlewhite.bmp"));

	*/

	
	//Rigid body
	btVector3 pos = GameEngine::Physics::irrVec3ToBtVec3(position);
	irr::core::vector3df a = _node->getTransformedBoundingBox().getExtent();
	//account for offset origin in model file
	pos.setY(pos.getY()+(scale.Y*a.Y*0.5f));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(pos);

	//setup shape
	btVector3 halfExtends(scale.X*a.X*0.5f,scale.Y*a.Y*0.5f,scale.Z*a.Z*0.5f);
	btCollisionShape* shape = new btBoxShape(halfExtends);

	//mass is 0, object is static, default motionstate
	btVector3 localInertia;
	shape->calculateLocalInertia(0,localInertia);
	btMotionState* motionstate = new btDefaultMotionState(transform);

	//create the RB
	_rigidBody = new btRigidBody(0,motionstate,shape,localInertia);
	//add to world
	GameEngine::Physics::world->addRigidBody(_rigidBody,GameEngine::Physics::E_Actor,GameEngine::Physics::E_ActorGroup);
	

	if(particles)
	{
		float particleRadius = _lightRange / (2.0f*scale.X);
		 // create a particle system
		irr::scene::IParticleSystemSceneNode* ps = GameEngine::engine.getDevice()->getSceneManager()->addParticleSystemSceneNode(false,_node);
		irr::scene::IParticleEmitter* em = ps->createRingEmitter(
			irr::core::vector3df(0,0,0),
			particleRadius / 2.0f,	//Ring Radius
			particleRadius,	//Ring thickness
			irr::core::vector3df(0.0f,0.06f,0.0f), //Direction
			3,			//Min particles per second
			80,		//Max particles per second
			irr::video::SColor(0,128,128,128),       // darkest color
			irr::video::SColor(0,255,255,255),      // brightest color
			800,		//Min Age
			2000,		//Max Age
			0,			//Angle			
			irr::core::dimension2df(5.0f,5.0f),     // min size
			irr::core::dimension2df(20.f,20.f)		// max size
			);        
		/*
		 irr::scene::IParticleEmitter* em = ps->createBoxEmitter(
			irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7), // emitter size
			irr::core::vector3df(0.0f,0.06f,0.0f),   // initial direction
			80,100,                             // emit rate
			irr::video::SColor(0,255,255,255),       // darkest color
			irr::video::SColor(0,255,255,255),       // brightest color
			800,2000,0,                         // min and max age, angle
			irr::core::dimension2df(10.f,10.f),         // min size
			irr::core::dimension2df(20.f,20.f));        // max size
		*/
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

		irr::scene::IParticleRotationAffector* pra = ps->createRotationAffector();
		pra->setPivotPoint(position);
		pra->setSpeed(irr::core::vector3df(0,30,10));
		ps->addAffector(pra);
		//pra->drop();
	}

	if(flame)
	{
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
		}
	}
	//set beacon to be unlit innitially
	light(false);
}

void Beacon::light(bool onOff)
{
	_isLit = onOff;
	if(_isLit)
	{
		_light->setRadius(_lightRange);
	}
	else
	{
		_light->setRadius(0.25f * _lightRange);
	}
}


void Beacon::intitalise()
{
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
