#pragma once
#include <irrlicht.h>

namespace GameEngine{
	/*! \brief An irr::IEventReceiver that parses for keyboard events.
	 *  \ingroup  Engine
	 */
	class KeyHandler : public irr::IEventReceiver{
		private:
			//! The states that a keyboard key can be in.
			enum keyStatesENUM { UP, DOWN, PRESSED, RELEASED };

			//! a boolean array used to determine if a key has been pressed and released
			bool firedKeys[irr::KEY_KEY_CODES_COUNT];

			//! An array holding the state of all keys
			keyStatesENUM keyState[irr::KEY_KEY_CODES_COUNT];
		public:
			//! Constructor, initialises arrays
			KeyHandler();

			//! Handle an event.
			bool OnEvent(const irr::SEvent& event);

			//! Update arrays
			void update();

			//! is a key PRESSED. This is used for specific edge case scenarios, most likely you want to use keyDOWN().
			bool keyPressed(char keycode);

			//! If a key is down, this will return true once, and then false any other time until the key is released and pressed again.
			bool keyFired(char keycode);

			//! is a key DOWN
			bool keyDown(char keycode);

			//! is a key UP
			bool keyUp(char keycode);

			//! is a key RELEASED. This is used for specific edge case scenarios, most likely you want to use keyUP().
			bool keyReleased(char keycode);

	};
}