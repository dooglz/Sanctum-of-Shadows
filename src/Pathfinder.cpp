#pragma once
#include "Pathfinder.h"
#include "Level.h"
#include <random>

std::default_random_engine Pathfinder::_generator;

// Find a random dark tile.
irr::core::vector2d<int> Pathfinder::getDarkLocation()
{	
	std::vector<irr::core::vector2d<int>> possibleLocations;

	for(unsigned int col = 0; col < Level::_grid.size(); col ++)
	{
		for(unsigned int row = 0; row < Level::_grid[col].size(); row ++)
		{
			if(Level::_grid[col][row] == Level::EMPTY || Level::_grid[col][row] ==  Level::BADLANDS)
			{
				possibleLocations.push_back(irr::core::vector2d<int>(col,row));
			}
		}
	}

	if (possibleLocations.size() > 1)
	{
		int seed = rand();
		if ( seed <= 0 ) { seed = 1;}
		_generator.seed (seed);
		std::uniform_int_distribution<int> distribution(0, possibleLocations.size()-1);
		return (possibleLocations[distribution(_generator)]);
	}
	else if (possibleLocations.size()  == 1)
	{
		return possibleLocations[0];
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
	std::uniform_real_distribution<float> distribution(-300.0,300.0);
	return irr::core::vector3df(pos.X+ distribution(_generator),40.0f,pos.Y+ distribution(_generator));
}

// Returns a vector3df at the center of a supplied grid coordinate, at height 100.0f
irr::core::vector3df Pathfinder::getResolvedLocation(irr::core::vector2d<int> coord){
	irr::core::vector2df pos = Level::getResolvedLocation(coord);
	return irr::core::vector3df(pos.X,40.0f,pos.Y);
}

// Get an adjacent Dark tile.
irr::core::vector2d<int> Pathfinder::getAdjacentDarkLocation(irr::core::vector2d<int> coord)
{
	std::vector<irr::core::vector2d<int>> possibleLocations;

	//UP
	if(coord.X > 0){
		if(Level::_grid[coord.X-1][coord.Y] == Level::EMPTY || Level::_grid[coord.X-1][coord.Y] == Level::BADLANDS)
		{
			possibleLocations.push_back(irr::core::vector2d<int>(coord.X-1,coord.Y));
		}
	}
	//Down
	if((unsigned int) coord.X < Level::_grid.size()-1){
		if(Level::_grid[coord.X+1][coord.Y] == Level::EMPTY || Level::_grid[coord.X+1][coord.Y] == Level::BADLANDS)
		{
			possibleLocations.push_back(irr::core::vector2d<int>(coord.X+1,coord.Y));
		}
	}
	//Left
	if(coord.Y > 0){
		if(Level::_grid[coord.X][coord.Y-1] == Level::EMPTY || Level::_grid[coord.X][coord.Y-1] == Level::BADLANDS)
		{
			possibleLocations.push_back(irr::core::vector2d<int>(coord.X,coord.Y-1));
		}
	}
	//Right
	if((unsigned int)coord.Y < Level::_grid[coord.X].size()-1){
		if(Level::_grid[coord.X][coord.Y+1] == Level::EMPTY || Level::_grid[coord.X][coord.Y+1] == Level::BADLANDS)
		{
			possibleLocations.push_back(irr::core::vector2d<int>(coord.X,coord.Y+1));
		}
	}

	if (possibleLocations.size() > 1)
	{
		int seed = rand();
		if ( seed <= 0 ) { seed = 1;}
		_generator.seed (seed);

		std::uniform_int_distribution<int> distribution(0, possibleLocations.size()-1);
		return (possibleLocations[distribution(_generator)]);
	}
	else if (possibleLocations.size()  == 1)
	{
		return possibleLocations[0];
	}

	//TODO display error.
	return coord;
}

irr::core::vector2d<int> Pathfinder::getResolvedCoord(irr::core::vector3df location)
{
	//we bounce this though here in case we need to do any additional logic to it in the future.
	return Level::getResolvedCoord(irr::core::vector2df(location.X,location.Z));
}