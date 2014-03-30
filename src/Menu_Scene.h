#pragma once
#include "GameState.h"
#include "beacon.h"

/*! \brief Main Menu Scene
 * \ingroup Game
 */
class Menu_Scene : public GameEngine::GameState{

	private:
		//Menu SceneNodes, if there were more, an array should be used to hold these. 

		//! Rotating Menu Camera
		irr::scene::ICameraSceneNode* menucam;

		//! floating billboard with Game Logo
		irr::scene::ISceneNode* logoNode;

		//! A Beacon
		Beacon* menuBeacon;

		//! Floor to receive Light
		irr::scene::IMeshSceneNode* floorNode;

	public: 
		//! Constructor.
		Menu_Scene();

		//! Destructor.
		~Menu_Scene();

		bool loadContent();

		void initialize();

		void flush();

		void update(float delta);

};