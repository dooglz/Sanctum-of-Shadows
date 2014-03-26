#pragma once
#include "driverChoice.h"
#include <string>
#include <irrlicht.h>
#include <iostream>
#include "KeyboardHandler.h"
#include "EntityManager.h"
#include "MeshManager.h"
#include "Physics.h"
#include "UI.h"
#include "BulletDebugDraw.h"
#include "irrKlang.h"
#pragma comment(lib, "irrKlang.lib")
/**
* \defgroup Engine Game Engine Classes
*/
namespace GameEngine{
	/*! \brief Handles initialising and running engine components and base Irrlicht functionality
	 *  \ingroup  Engine
	 */
	class Engine{
		private:
			//! A pointer to the Irrlicht Device
			irr::IrrlichtDevice* _device;

			//! The Window title
			std::wstring _caption;

			//! The Window dimensions
			irr::core::dimension2d<irr::u32> _dimensions;

			//! Set to false to exit the main loop
			bool _run;
		public:
			//! constructor
			Engine(){}

			//! destructor
			~Engine(){}

			//! the sound engine
			 static irrklang::ISoundEngine* soundengine;
			//! Calls initialise() on various components and creates the irrlicht device.
			bool initialise();

			//! Updates engine functions and physics
			bool update(float delta);

			//! Render the frame.
			bool render();

			//! Shuts down components and closes the irrlicht device.
			void shutdown();

			//! Set's run to false.
			void stop();

			//! Returns _run.
			bool run()
			{
				return _run;
			}

			//! Returns_device.
			irr::IrrlichtDevice* getDevice()
			{ 
				return _device; 
			}

			//! Returns _caption.
			std::wstring getCaption() const 
			{ 
				return _caption; 
			}
			
			//! Sets the Window caption.
			void setCaption(const std::wstring& value)
			{
				_caption = value;
				//_device->setWindowCaption(_caption.c_str());
			}
			
			//! Returns _dimensions.
			irr::core::dimension2d<irr::u32> getDimensions() const
			{
				return _dimensions;
			}
			
			//! Sets _dimensions.
			void setDimensions(const irr::core::dimension2d<irr::u32>& value)
			{
				_dimensions = value;
			}
	};

	//! The primary Engine instance.
	extern Engine engine;

	//! The keyboard handler
	extern KeyHandler handler;

	//! The MeshManager
	extern MeshManager meshManager;

	//! The UI Manager
	extern UI ui;
}