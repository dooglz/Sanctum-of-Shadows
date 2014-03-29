#include "Pathfinder.h"
#include "Level.h"

irr::core::vector3df Pathfinder::getDarkLocation()
{	

	for(unsigned int col = 0; col < Level::_grid.size(); col ++)
	{
		for(unsigned int row = 0; row < Level::_grid[col].size(); row ++)
		{
			if(Level::_grid[col][row] == Level::EMPTY)
			{
				if (rand() % 100 < 10) {
					irr::core::vector3df pos  =Level::getResolvedLocation(col,row);
					pos.Y = pos.Y + 100.0f;
					return pos;
				}
			}
		}
	}


	return irr::core::vector3df(0,0,0);
}