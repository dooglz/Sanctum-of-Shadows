#pragma once
#include <irrlicht.h>
#include <string>

namespace GameEngine{
	/*! \brief A Scene.
	 * \ingroup Engine
	 */
	class EntityManager;
	class Scene{ 
		protected : 

			//! A unique name, used for identification.
			std::string _name;

			//! Each Scene has it's own Entity Manager.
			EntityManager* _entityManager;
 
		public : 

			//! Default Constructor
			Scene () ; 

			//! Constructor
			Scene (std::string name);

			//! Destructor.
			~Scene (){};

			//! All resources (textures/meshes) should be loaded and assigned in this function.
			virtual bool loadContent() = 0;
 
			//!Initialize the Scene, setup gui or something 
			virtual void initialize () = 0;
 
			//! Clean up the Scene
			virtual void flush () = 0;
			
			//! Process per frame logic.
			virtual void update(float delta) = 0;

			//! Get Scene name
			std::string getName(){return _name;}

			//! Get the Entity Manger for this Scene
			EntityManager* getEntityManager();
	} ;
}