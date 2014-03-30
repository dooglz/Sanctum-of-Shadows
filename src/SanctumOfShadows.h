/**
 * \defgroup Game Game Specific Classes
 */

#pragma once
#include "Game.h"

/*! \brief Primary Game logic for Sanctum of Shadows
 * \ingroup Game
 */
class SanctumOfShadows:public Game{

	public:

		//! Constructor.
		SanctumOfShadows();

		//! Destructor.
		~SanctumOfShadows();

		//! Creates Required Entities.
		bool init();

		//! Run per-frame game logic.
		bool update(float delta);

};


