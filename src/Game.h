#pragma once
#include <irrlicht.h>
#include <iostream>
/*! \brief Baseclass for gamelogic, bridge between engine and game code.
 * \ingroup Engine
 */
class Game{
protected:
	//! Title of the game
	std::wstring _gameTitle;

	//! Starting dimensions
	irr::core::dimension2d<irr::u32> _resolution;

public:

	//! Constructor.
	Game(){};
	
	//! Destructor.
	virtual ~Game(){};

	//! Initialise.
	virtual bool init() = 0;

	//! Run per-frame game logic.
	virtual bool update(float delta) = 0;

	//! Returns _gameTitle. 
	std::wstring getGametitle(){
		return _gameTitle;
	}

	//! Returns _resolution. 
	irr::core::dimension2d<irr::u32> getResolution(){
		return _resolution;
	}

};