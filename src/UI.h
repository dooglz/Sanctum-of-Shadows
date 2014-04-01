#pragma once
#include <irrlicht.h>
#include <vector>
#include "CGUITTFont.h"

namespace GameEngine{
	/*! \brief User interface utilities
	 *  \ingroup  Engine
	 */
	class UI{
		public:
			//! A Text Message is displayed on screen for a certain amount of frames
			struct TextMessage {
				//! Message to display
				irr::core::stringw message;

				//TODO make this time, rather than frames.
				//! Frames left before the message is removed
				unsigned int timeLeft;
			};

			//! Default constructor.
			UI() {};

			//! Destructor.
			~UI();

			//! Create a new text message, set time to 0 to display for 1 frame only.
			static void displayTextMessage(const irr::core::stringw& message,const unsigned int time);

			//! Create a new text message in the center of the screen, set time to 0 to display for 1 frame only.
			static void displayBigMessage(const irr::core::stringw& message,const unsigned int time);

			//! Process stored and queued UI data.
			static void update();

			//! Draw UI elements. 
			static void render();

			//! Clear Messages. 
			static void clear();

			static void initialise(irr::IrrlichtDevice* dev);

		private:
			static TextMessage _bigmessage;

			//! Vector containing all text messages. Unsorted.
			static std::vector<TextMessage> _textMessages;

			//! Font to use. 
			static irr::gui::CGUITTFont* _font;
			static irr::gui::CGUITTFont* _bigfont;

			//! Font Colour to use. 
			static irr::video::SColor _colour;

	};

}