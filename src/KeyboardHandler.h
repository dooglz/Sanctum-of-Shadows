#pragma once
#include <irrlicht.h>

namespace GameEngine{
	class KeyHandler : public irr::IEventReceiver{
		private:
			enum keyStatesENUM { UP, DOWN, PRESSED, RELEASED };
			bool firedKeys[irr::KEY_KEY_CODES_COUNT];
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
							keyState[event.KeyInput.Key] = PRESSED;
						}
						// if key was down before
						else 
						{
							//Technically this line should set it to equal HOLD, but as we can't determine it accuratly, just stick to DOWN
							//key repeat timing is set by the os, so for a few fames a key will be registered as pressed rather than down, untill the repeat event comes in.
							//This is why we set pressed keys to be down immediatly in update()
 							keyState[event.KeyInput.Key] = DOWN; // Set to Down
						}
					}
					else
					{
						// if the key is down
						if (keyState[event.KeyInput.Key] != UP)
						{
							keyState[event.KeyInput.Key] = RELEASED;
						}
					}
				}
				return false;
			}

			void update(){
				for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i){
					if(keyState[i] == RELEASED)
					{
						keyState[i] = UP;
						firedKeys[i] = false;
					}
					else if(keyState[i] == PRESSED)
					{
						keyState[i] = DOWN;
					}
				}
			}

			bool keyPressed(char keycode)
			{
				if ( keyState[keycode] == PRESSED)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			bool keyFired(char keycode)
			{
				if (firedKeys[keycode])
				{
					//key has been fired,
					return false;
				}
				else if (!firedKeys[keycode] && keyState[keycode] == DOWN)
				{
					firedKeys[keycode] = true;
					return true;
				}
				else
				{
					return false;
				}
			}

			bool keyDown(char keycode)
			{
				if (keyState[keycode] == DOWN)
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
				if (keyState[keycode] == UP)
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