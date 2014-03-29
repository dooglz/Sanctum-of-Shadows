#include "Pathfinder.h"
#include "Level.h"

irr::core::vector3df Pathfinder::getDarkLocation()
{	
	irr::core::vector3df pos ;
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
						pos = Level::getResolvedLocation(col,row);
						found = true;
					}
				}
			}
		}
	}

	pos.Y = pos.Y + 100.0f;
	return pos;
}