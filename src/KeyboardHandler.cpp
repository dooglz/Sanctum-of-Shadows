#pragma once
#include <irrlicht.h>
#include "KeyboardHandler.h"

namespace GameEngine{

		// Constructor, initialises arrays
		KeyHandler::KeyHandler(){
			for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i){
				keyState[i] = UP;
			}
		}

		// Handle an event.
		bool KeyHandler::OnEvent(const irr::SEvent& event){
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
						//Technically this line should set it to equal HOLD, but as we can't determine it accurately, just stick to DOWN
						//key repeat timing is set by the OS, so for a few fames a key will be registered as pressed rather than down, until the repeat event comes in.
						//This is why we set pressed keys to be down immediately in update()
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

		
		// Update arrays
		void KeyHandler::update(){
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

		// is a key PRESSED. This is used for specific edge case scenarios, most likely you want to use keyDOWN().
		bool KeyHandler::keyPressed(char keycode)
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

		// If a key is down, this will return true once, and then false any other time until the key is released and pressed again.
		bool KeyHandler::keyFired(char keycode)
		{
			if (firedKeys[keycode])
			{
				//key has already been fired.
				return false;
			}
			else if (!firedKeys[keycode] && keyState[keycode] == DOWN)
			{
				firedKeys[keycode] = true;
				return true;
			}
			else
			{
				//key is not down
				return false;
			}
		}

		// is a key DOWN
		bool KeyHandler::keyDown(char keycode)
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

		// is a key UP
		bool KeyHandler::keyUp(char keycode)
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

		// is a key RELEASED. This is used for specific edge case scenarios, most likely you want to use keyUP().
		bool KeyHandler::keyReleased(char keycode)
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

}