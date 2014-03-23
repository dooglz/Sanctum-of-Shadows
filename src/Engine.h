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
/**
* \defgroup Engine Game Engine Classes
*/
namespace GameEngine{
	/*! \brief Hanldes initialising and running engine components and base Irrlicht functionality
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

			//! Calls initialise() on various components and creates the irrlicht device.
			bool initialise();

			//! Updates engine functions and physics
			bool update(float delta);

			bool render();

			//todo remove
			void unloadContent();

			//! shuts down components and closes the irrlicht device
			void shutdown();

			//! Set's run to false;
			void stop();

			//getsets
			bool run()
			{
				return _run;
			}

			irr::IrrlichtDevice* getDevice()
			{ 
				return _device; 
			}

			std::wstring getCaption() const 
			{ 
				return _caption; 
			}

			void setCaption(const std::wstring& value)
			{
				_caption = value;
				//_device->setWindowCaption(_caption.c_str());
			}

			irr::core::dimension2d<irr::u32> getDimensions() const
			{
				return _dimensions;
			}

			void setDimensions(const irr::core::dimension2d<irr::u32>& value)
			{
				_dimensions = value;
			}
	};

	extern Engine engine;
	extern KeyHandler handler;
	extern MeshManager meshManager;
	extern UI ui;
}