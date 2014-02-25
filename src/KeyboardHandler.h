#pragma once
#include <irrlicht.h>

namespace GameEngine{
	class KeyHandler : public irr::IEventReceiver{
		private:
			enum keyStatesENUM { UP, DOWN, PRESSED, RELEASED };
			keyStatesENUM keyState[irr::KEY_KEY_CODES_COUNT];
		public:
			KeyHandler(){
				for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i){
					keyState[i] = UP;
				}
			}
			bool OnEvent(const irr::SEvent& event){
				if (event.EventType == irr::EET_KEY_INPUT_EVENT){
					// if key is Pressed Down

					if (event.KeyInput.PressedDown == true)
					{
						// If key was not down before
						if (keyState[event.KeyInput.Key] != DOWN  && keyState[event.KeyInput.Key] != PRESSED)
						{
							keyState[event.KeyInput.Key] = PRESSED; // Set to Pressed
						}
						else
						{
							//key repeat timing is set by the os, so for a few fames a key will be registered as pressed rather than down, untill the repeat event comes in.
							// if key was down before
 							keyState[event.KeyInput.Key] = DOWN; // Set to Down
						}
					}
					else
					{
						// if the key is down
						if (keyState[event.KeyInput.Key] != UP)
						{
							keyState[event.KeyInput.Key] = RELEASED; // Set to Released
						}
					}
				}
				//std::cout << " -> " << keyState[event.KeyInput.Key] << std::endl;
				return false;
			}
			bool keyPressed(char keycode)
			{
				if (keyState[keycode] == PRESSED)
				{
					//std::cout << keyState[keycode] << std::endl;
					return true;
				}
				else
				{
					return false;
				}
			}

			bool keyDown(char keycode)
			{
				if (keyState[keycode] == DOWN || keyState[keycode] == PRESSED)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			bool keyUp(char keycode)
			{
				if (keyState[keycode] == UP || keyState[keycode] == RELEASED)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			bool keyReleased(char keycode)
			{
				if (keyState[keycode] == RELEASED)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

	};
}