/*===============================================================================
  Class:   Engine
  Inherits from:  None
  Author:   Sam Serrels
  Purpose:  0000
===============================================================================*/
#pragma once

#include <string>
#include <irrlicht.h>
#include "KeyboardHandler.h"
#include "EntityManager.h"

#include "MeshManager.h"
#include "Physics.h"


namespace GameEngine{
	class Engine{
		private:
			irr::IrrlichtDevice* _device;
			std::wstring _caption;
			irr::core::dimension2d<irr::u32> _dimensions;
			irr::scene::ICameraSceneNode* _camera;
		public:
			//constructor
			Engine(){}
			//destructor
			~Engine(){}
			//getsets
			irr::IrrlichtDevice* getDevice(){ return _device; }
			std::wstring getCaption() const { return _caption; }
			void setCaption(const std::wstring& value){
				_caption = value;
				//_device->setWindowCaption(_caption.c_str());
			}
			irr::core::dimension2d<irr::u32> getDimensions() const{
				return _dimensions;
			}
			void setDimensions(const irr::core::dimension2d<irr::u32>& value){
				_dimensions = value;
			}
			irr::scene::ICameraSceneNode* getCamera(){
				return _camera;
			}
			void setCamera(irr::scene::ICameraSceneNode* camera){
				_camera = camera;
			}
			//funcs
			bool initialise();
			bool loadContent();
			bool update(float delta);
			bool render();
			void unloadContent();
			void shutdown();
			void debug();
	};

	extern Engine engine;
	extern KeyHandler handler;
	extern MeshManager meshManager;
}