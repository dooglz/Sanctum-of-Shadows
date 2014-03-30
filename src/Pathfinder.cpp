#include "Pathfinder.h"
#include "Level.h"

// Find a random dark tile.
irr::core::vector2d<int> Pathfinder::getDarkLocation()
{	
	//Runaway loop protection, limit to 500 loops
	unsigned int limit = 0;

	while(limit < 500)
	{
		for(unsigned int col = 0; col < Level::_grid.size(); col ++)
		{
			for(unsigned int row = 0; row < Level::_grid[col].size(); row ++)
			{
				if(Level::_grid[col][row] == Level::EMPTY)
				{
					if (rand() % 100 < 5) {
						return irr::core::vector2d<int>(col,row);
					}
				}
			}
		}
		limit++;
	}
	//TODO display error.
	return irr::core::vector2d<int>(0,0);
}

// Find a random location within a tile.
irr::core::vector3df Pathfinder::getLocationWithinTile(irr::core::vector2d<int> coord)
{
	//get tile position
	irr::core::vector2df pos;
	pos = Level::getResolvedLocation(coord);
	//Find a random location within it
		//TODO
	return irr::core::vector3df(pos.X,100.0f,pos.Y);
}

// Returns a vector3df at the center of a supplied grid coordinate, at height 100.0f
irr::core::vector3df Pathfinder::getResolvedLocation(irr::core::vector2d<int> coord){
	irr::core::vector2df pos = Level::getResolvedLocation(coord);
	return irr::core::vector3df(pos.X,100.0f,pos.Y);
}