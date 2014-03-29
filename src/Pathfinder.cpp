#include "Pathfinder.h"
#include "Level.h"

irr::core::vector3df Pathfinder::getDarkLocation()
{	
	irr::core::vector3df pos;
	bool found = false;

	while(!found)
	{
		for(unsigned int col = 0; col < Level::_grid.size(); col ++)
		{
			for(unsigned int row = 0; row < Level::_grid[col].size(); row ++)
			{
				if(Level::_grid[col][row] == Level::EMPTY)
				{
					if (rand() % 100 < 5) {
						pos = Level::getResolvedLocation(irr::core::vector2d<int>(col,row));
						found = true;
					}
				}
			}
		}
	}

	pos.Y = pos.Y + 100.0f;
	return pos;
}

irr::core::vector3df Pathfinder::getLocationWithinTile(irr::core::vector2d<int> coord)
{
	//get tile position
	irr::core::vector3df pos;
	pos = Level::getResolvedLocation(coord);
	return pos;
}