#pragma once
#include <irrlicht.h>
#include <string>
#include "EntityManager.h"

namespace GameEngine{
	/*! \brief A Scene.
	 * \ingroup Engine
	 */
	class GameState{ 
		protected : 

			//! A unique name, used for identification.
			std::string _name;

			//! Each Scene has it's own Entity Manager.
			EntityManager* _entityManager;
 
		public : 

			//! Default Constructor
			GameState () ; 

			//! Constructor
			GameState (std::string name):_name(name){};

			//! Destructor.
			~GameState (){};

			//! All resources (textures/meshes) should be loaded and assigned in this function.
			virtual bool loadContent() = 0;
 
			//!Initialize the game state, setup gui or something 
			virtual void initialize () = 0;
 
			//! Clean up the game state 
			virtual void flush () = 0;
			
			//! Process per frame logic.
			virtual void update(float delta) = 0;

			//! Render all the stuff
			virtual void render () =  0;  

			//! Get name of game state 
			std::string getName(){return _name;}
	} ;
}