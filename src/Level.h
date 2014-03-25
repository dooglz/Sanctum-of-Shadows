#pragma once
#include "Entity.h"
#include <array>
#include <ctime>

/*! \brief Primary Game logic for Sanctum of Shadows
 * \ingroup Game
 */
class Level: public GameEngine::Entity{
	private:

		//level gen stuff
		//@{
			//! Grid size, X by X, has to be an odd number.
			static const unsigned int _gridSize = 7;
			//! amount of dark tiles lining the edge.
			static const unsigned int _darkPadding = 1;
			//! Max obstacles to spawn around a beacon.
			static const unsigned int _maxObstacles = 2; 
		//@}

		//! The tiles types that make up a level.
		static const enum tile {EMPTY,BADLANDS,BEACON,OBSTACLE};

		//! The level Grid.
		static std::array<std::array<tile,_gridSize>, _gridSize> _grid;

		//! Place beacons in the level.
		void placeBeacons();

		//! Procedurally generate the level, populates _grid.
		void generateLevel();

		//! Spawn the entities and geometry as laid out by generateLevel().
		void createLevel();

		//! The bullet ground plane.
		btRigidBody* _groundPlaneRB;

	public:

		//! Constructor
		Level() :Entity(-1,0,"Level"){};

		//! Destructor.
		~Level(){};

		//! Generate and Create level.
		void intitalise();

		//! Load level meshes
		bool loadContent();

		//! Does Nothing
		void update(float delta){};
};