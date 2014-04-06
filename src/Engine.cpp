#include "Engine.h"
#include "Utilities.h"


namespace GameEngine{

	// The sound engine
	irrklang::ISoundEngine* Engine::soundengine;

	// The random generator to use throughout the gamelogic
	std::default_random_engine Engine::generator;

	// The primary Engine instance.
	Engine engine = Engine();

	// The keyboard handler
	KeyHandler handler = KeyHandler();
	
	// The UI Manager
	UI ui = UI();

	//--- Physics Debug
	irr::video::SMaterial debugMat;
	DebugDraw* debugDraw;
	// ---

	// Calls initialise() on various components and creates the irrlicht device.
	bool Engine::initialise(){

		irr::video::E_DRIVER_TYPE driverType;
	
		if(DEVELOPER_MODE)
		{
			// ask for driver
			driverType=irr::driverChoiceConsole();
			if (driverType==irr::video::EDT_COUNT)
				return 1;
		}
		else
		{
			// Default driver
			driverType = irr::video::EDT_DIRECT3D9;
		}

		// TODO investigate if vsync can be toggled
		_device = irr::createDevice(driverType, _dimensions, 16, FULLSCREEN, true, VSYNC, &handler);
		
		if (!_device){
			std::cerr << "Error creating device" << std::endl;
			return false;
		}

		_run = true;
		_device->setWindowCaption(_caption.c_str());

		// Textures need to be 32bit to allow for normal maps
		_device->getVideoDriver()->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);

		// Initialise sound engine
		soundengine = irrklang::createIrrKlangDevice();

		// Initialise UI Manager
		UI::initialise(_device);

		// Initialise Physics
		Physics::initialise();
		
		// Physics debug ------
		_debug_draw_bullet = false;
		debugDraw = new DebugDraw(_device);
		debugDraw->setDebugMode(
				btIDebugDraw::DBG_DrawWireframe |
				btIDebugDraw::DBG_DrawAabb |
				btIDebugDraw::DBG_DrawContactPoints |
				btIDebugDraw::DBG_DrawText |
				//btIDebugDraw::DBG_DrawConstraintLimits |
				btIDebugDraw::DBG_DrawConstraints //|
		);
		Physics::world->setDebugDrawer(debugDraw);
		debugMat.Lighting = false;
		// -----

		// Seed the random Generator
		int seed = rand();
		if ( seed <= 0 ) { seed = 1;}
		generator.seed (seed);

		return true;
	}

	// Updates engine functions and physics
	bool Engine::update(float delta){
		handler.update();
		ui.update();

		if(!MessageHandler::update())
		{
			return false;
		}
		
		//2nd param is physics ticks per second.
		Physics::world->stepSimulation(delta,60);

		return true;
	}

	// Render the frame.
	bool Engine::render(){

		if (!_device->getVideoDriver()->beginScene()){
			return false;
		}

		// Render Scene
		_device->getSceneManager()->drawAll();
		// Render UI
		_device->getGUIEnvironment()->drawAll();
		
		
		if(DEVELOPER_MODE && _debug_draw_bullet)
		{
			//Render Physics Debug
			_device->getVideoDriver()->setMaterial(debugMat);
			_device->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
			Physics::world->debugDrawWorld();
		}

		//Render UI
		ui.render();

		if (!_device->getVideoDriver()->endScene()){
			return false;
		}
		return true;
	}

	//Shuts down components and closes the irrlicht device.
	void Engine::shutdown(){
		
		if(soundengine != nullptr)
		{
			soundengine->stopAllSounds();
			soundengine->drop();
			soundengine = NULL;
		}

		if(_device!= nullptr)
		{
			_device->closeDevice();
			_device = NULL;
		}

		//TODO do we not shutdown physics? Is this not what we came here to see?

	}

	// Set's run to false.
	void Engine::stop(){
		_run = false;
	}

}