#pragma once
#include "Entity.h"
#include "Beacon.h"
#include "Obstacle.h"
#include <iostream>
#include <vector>
#include <array>

/* ! \brief Primary Game logic for Sanctum of Shadows
 * \ingroup Game
 */

class Level: public GameEngine::Entity{
	private:


		//level gen stuff
		//@{
			//! Grid size, X by X, has to be an odd number.
			static const unsigned int _gridSize = 11;
			//! amount of dark tiles lining the edge.
			static const unsigned int _darkPadding = 1;
			//! Physical size of each tile in the grid.
			static const unsigned int _tileSize = 800; 
			//! Chance of placing a beacon in an available slot
			static const unsigned int _beaconPercent = 10; 
			//! Should all available slots for beacons be filled?
			static const bool _beaconFill = false; 
			//! Chance of placing a beacon in an available slot
			static const unsigned int _obstaclePercent = 80; 
		//@}

		//! Procedurally generate the level, populates _grid.
		void generateLevel();

		//! Spawn the entities and geometry as laid out by generateLevel().
		void createLevel();

		//! The bullet ground plane.
		btRigidBody* _groundPlaneRB;

		//! Vector of all the floortiles
		std::vector< irr::scene::IMeshSceneNode* > _floorTiles;

		//! Vector of all the obstacles
		std::vector< Obstacle* > _obstacles;

		//! Vector of all the beacons
		std::vector< Beacon* > _beacons;

		//! Is Lighting enabled on the level, used for debug
		bool _isLit;



	public:
		//! The tiles types that make up a level.
		static const enum tile {EMPTY,BADLANDS,BEACON,OBSTACLE};

		//! Constructor
		Level(GameEngine::Scene* parentScene);

		//! Destructor.
		~Level();

		//! Generate and Create level.
		void intitalise();

		//! Load level meshes
		bool loadContent();

		//! Does Nothing
		void update(float delta){};

		//! Sets EMF_LIGHTING on all level nodes, used for debug.
		void toggleLighting(bool a);

		//! Are all the beacons lit?
		bool allBeaconsLit();

		//! The level Grid.
		static std::array<std::array<tile,_gridSize>, _gridSize> _grid;

		//! Is Lighting enabled on the level.
		bool isLit()
		{
			return _isLit;
		}

		//! Returns a vector2df at the center of a supplied grid coordinate
		static irr::core::vector2df getResolvedLocation(irr::core::vector2d<int> coord);

		//! Returns a vector2d<int> grid coordinate that contains the supplied position, Clamps between 0 and _gridSize.
		static irr::core::vector2d<int> getResolvedCoord(irr::core::vector2df location);
};