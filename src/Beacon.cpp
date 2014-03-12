#include "Beacon.h"
#include "Engine.h"
#include "Player.h"
#include "SanctumOfShadows.h"

#include <iostream>

Beacon::Beacon(const irr::core::vector3df& position) : GameEngine::Entity(-1,0,"Beacon")
{
	bool particles = false;
	bool flame = false;
	bool light = true;
	_alive = true;

	//scene node
	loadContent();
	_node->setScale(irr::core::vector3df(15,15,15));
	_node->setPosition(position);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, true);

	//set a healing range to heal the player
	_range = 150;

	
	
	// create light
	if(light)
	{

	_light = 0;
	//_light = GameEngine::engine.getDevice()->getSceneManager()->addLightSceneNode();
	
	
	_light = GameEngine::engine.getDevice()->getSceneManager()->addLightSceneNode(
		_node, irr::core::vector3df(0,7.0f,0),			//Parent and offset
		irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f),	//Colour
		500.0f);	//Radiius
	
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

	/* 
	//Rigid body
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(position);
	GameEngine::MotionState* motionstate = new GameEngine::MotionState(btTransform(btQuaternion(0.0, 0.0, 0.0, 1.0), position), _node);

	//setup shape
	btVector3 halfExtends(scale.X*0.5f,scale.Y*0.5f,scale.Z*0.5f);
	btCollisionShape* shape = new btBoxShape(halfExtends);

	//calc intertia, based on mass and shape
	btVector3 localInertia;
	shape->calculateLocalInertia(mass,localInertia);

	//create the RB
	_rigidBody = new btRigidBody(mass,motionstate,shape,localInertia);
	//add to world
	GameEngine::Physics::world->addRigidBody(_rigidBody,GameEngine::Physics::E_Actor,GameEngine::Physics::E_ActorGroup);
	*/
	}

	if(particles)
	{
		 // create a particle system
		irr::scene::IParticleSystemSceneNode* ps = GameEngine::engine.getDevice()->getSceneManager()->addParticleSystemSceneNode(false,_node);
		irr::scene::IParticleEmitter* em = ps->createRingEmitter(
			irr::core::vector3df(0,0,0),
			6.0f,2.0f,
			irr::core::vector3df(0.0f,0.06f,0.0f),
			30,80,
			irr::video::SColor(0,255,255,255),       // darkest color
			irr::video::SColor(0,255,255,255),      // brightest color
			800,2000,0,								// min and max age, angle
			irr::core::dimension2df(10.f,10.f),     // min size
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

}

void Beacon::intitalise()
{
}

bool Beacon::loadContent()
{
	irr::scene::IAnimatedMesh* cube = GameEngine::engine.getDevice()->getSceneManager()->getMesh("models/beacon.obj");
	if (!cube)
	{
		std::cerr << "Error loading Mesh" << std::endl;
		return false;
	}
	_node = GameEngine::engine.getDevice()->getSceneManager()->addAnimatedMeshSceneNode(cube);
	return true;
}

void Beacon::update(float delta)
{
	if((SanctumOfShadows::player->getNode()->getPosition() - _node->getPosition()).getLength() < _range)
	{
		float a = SanctumOfShadows::player->getHealth();
		if( a < 150.0f)
		{
			//player getting healed by beacon
			SanctumOfShadows::player->setHealth( a + (5.0f * delta));
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
