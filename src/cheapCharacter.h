#pragma once
#include <irrlicht.h>
#include "Character.h"

/*! \brief A character that has no bullet collision, movement controlled by irrlicht
 *  \ingroup Game
 */

class cheapCharacter: public Character{
	protected:

		//@{
		irr::core::vector3df _forwardDir;
		irr::core::vector3df _upDir;
		irr::core::vector3df _strafeDir;
		//@}

		//! Current bullet transform of the character
		irr::core::matrix4  _xform;

		//! current position in Irrlicht space, updated by Walk().
		irr::core::vector3df _position;

		//! Move based on the walk flags.
		void walk(float delta);

	public:
		//! Constructor, implemented only to pass name and ID to Entity constructor.
		cheapCharacter(GameEngine::Scene* parentScene,const std::string& name);

		//! Destructor.
		~cheapCharacter();

		//! Creates the controller and adds a blank scene node.
		void intitalise(irr::core::vector3df position, irr::core::vector3df size);

		//! Recalculate position transforms and direction vectors, call this before Walk.
		void update(float delta);

		//! Creates the controller and adds a blank scene node.
		void intitalise(){};
};