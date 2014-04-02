#pragma once
#include <irrlicht.h>

/*! \brief Pathfinding, and grid traversal logic.
 * \ingroup Game
 */
class Pathfinder{

	private:
		//! Constructor.
		Pathfinder();

		//! Destructor.
		~Pathfinder(); 
	public:

		//! Get an adjacent Dark tile.
		static irr::core::vector2d<int> getAdjacentDarkLocation(irr::core::vector2d<int> coord);

		//! Find a random dark tile.
		static irr::core::vector2d<int> getDarkLocation();

		//! Find a random location within a tile.
		static irr::core::vector3df getLocationWithinTile(irr::core::vector2d<int> coord);

		//! Returns a vector3df at the center of a supplied grid coordinate, at height 100.0f
		static irr::core::vector3df getResolvedLocation(irr::core::vector2d<int> coord);

		//! Returns a vector2d<int> grid coordinate that contains the supplied position, Clamps between 0 and _gridSize.
		static irr::core::vector2d<int> getResolvedCoord(irr::core::vector3df location);
};