#include "UI.h"

namespace GameEngine{

	// Font to use for notifications. 
	irr::gui::CGUITTFont* UI::_font;

	// Font to use for large center notification
	irr::gui::CGUITTFont* UI::_bigfont;

	// Font Colour to use. 
	irr::video::SColor UI::_colour;

	// The large center notification, their can only be one displayed at a time.
	UI::TextMessage UI::_bigmessage;

	// Vector containing all text messages. Unsorted.
	std::vector<UI::TextMessage> UI::_textMessages;

	// Uses device to setup fonts. 
	void UI::initialise(irr::IrrlichtDevice* dev){

		_colour = irr::video::SColor(255,255,255,255);

		//Load TrueType Font to CGUITTFace
		irr::gui::IGUIEnvironment* env = dev->getGUIEnvironment();

		//TODO scale font size with resolution.
		_font =  irr::gui::CGUITTFont::createTTFont(env, "fonts/CelticGaramond.ttf", 30);
		_bigfont = irr::gui::CGUITTFont::createTTFont(env, "fonts/CelticGaramond.ttf", 50);
		//_font = _device->getGUIEnvironment()->getBuiltInFont();

		// Set the font.
		irr::gui::IGUISkin* skin = env->getSkin();
		skin->setFont(_font);
 
	}

	// Destructor.
	UI::~UI()
	{
		if (_font != nullptr )
		{
			_font->drop();
			_font = NULL;
		}

		_textMessages.clear();
	}
	
	// Create a new text message, set time to 0 to display for 1 frame only.
	void UI::displayTextMessage(const irr::core::stringw& message, const unsigned int time){
		TextMessage m;
		m.message = message;
		m.timeLeft = time;
		_textMessages.push_back(m);
	}

	// Create a new text message, set time to 1 to display for 1 frame only.
	void UI::displayBigMessage(const irr::core::stringw& message, const unsigned int time){
		TextMessage m;
		m.message = message;
		m.timeLeft = time;
		_bigmessage = m;
	}

	// Process stored and queued UI data
	void UI::update(){
		std::vector<UI::TextMessage>::iterator it = _textMessages.begin();
		for ( ; it !=  _textMessages.end(); ) {
			if (it->timeLeft <= 0) {
				it =  _textMessages.erase(it);
			  } else {
				it->timeLeft --;
				++it;
			  }
		}
		if (_bigmessage.timeLeft > 0) {
			_bigmessage.timeLeft --;
		}
	}

	// Draw UI elements
	void UI::render(){
		for (unsigned int i=0; i<_textMessages.size(); i++) {
			_font->draw(_textMessages[i].message,irr::core::rect<irr::s32>(130,10+(i*35),300,50+(i*35)),_colour);
		}
		if (_bigmessage.timeLeft > 0) {
			_bigfont->draw(_bigmessage.message,irr::core::rect<irr::s32>( (1280/2) - (_bigmessage.message.size()/2)*50 ,340,1280,380),_colour);
		}
	}

	// Clear Messages.
	void UI::clear()
	{
		_textMessages.clear();
	}
}