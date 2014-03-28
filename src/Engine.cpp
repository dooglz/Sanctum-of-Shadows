#include "Engine.h"


namespace GameEngine{
	irrklang::ISoundEngine* Engine::soundengine;
	Engine engine = Engine();
	KeyHandler handler = KeyHandler();
	UI ui;
	irr::video::SMaterial debugMat;
	DebugDraw* debugDraw;

	// Calls initialise() on various components and creates the irrlicht device.
	bool Engine::initialise(){

		// ask user for driver
		irr::video::E_DRIVER_TYPE driverType=irr::driverChoiceConsole();
		if (driverType==irr::video::EDT_COUNT)
			return 1;

		_run = true;
		_device = irr::createDevice(
			driverType, _dimensions, 16, false, true, false, &handler);
		//TODO investigate if vsync can be toggled
		if (!_device){
			std::cerr << "Error creating device" << std::endl;
			return false;
		}
		_device->setWindowCaption(_caption.c_str());
		_device->getVideoDriver()->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);
		
		if(!EntityManager::initialise())
		{
			return false;
		}
		
		Physics::initialise();

		soundengine = irrklang::createIrrKlangDevice();

		//physics debug
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


		ui = UI(_device);
		return true;
	}

	// Updates engine functions and physics
	bool Engine::update(float delta){
		handler.update();
		ui.update();
		if(!EntityManager::update(delta))
		{
			return false;
		}
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
		_device->getSceneManager()->drawAll();
		_device->getGUIEnvironment()->drawAll();
		
		if(_debug_draw_bullet)
		{
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
		EntityManager::shutdown();
		if(_device)
		{
			_device->closeDevice();
			_device = NULL;
		}
	}

	// Set's run to false.
	void Engine::stop(){
		_run = false;
	}

}