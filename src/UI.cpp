#include "UI.h"

namespace GameEngine{
	irr::gui::CGUITTFont* UI::_font;
	irr::video::SColor UI::_colour;
	std::vector<UI::TextMessage> UI::_textMessages;

	UI::UI(irr::IrrlichtDevice* dev){

		
		_colour = irr::video::SColor(255,255,255,255);

		//Load TrueType Font to CGUITTFace
		irr::gui::IGUIEnvironment* env = dev->getGUIEnvironment();

		//TODO scale font size with resolution.
		_font =  irr::gui::CGUITTFont::createTTFont(env, "fonts/CelticGaramond.ttf", 30);

		//_font = _device->getGUIEnvironment()->getBuiltInFont();

		// Set the font.
		irr::gui::IGUISkin* skin = env->getSkin();
		skin->setFont(_font);
 
	}

	UI::~UI()
	{
		_font->drop();
		_textMessages.clear();
	}
	
	// Create a new text message, set time to 0 to display for 1 frame only.
	void UI::displayTextMessage(const irr::core::stringw& message, const unsigned int time){
		TextMessage m;
		m.message = message;
		m.timeLeft = time;
		_textMessages.push_back(m);
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
	}

	// Draw UI elements
	void UI::render(){
		for (unsigned int i=0; i<_textMessages.size(); i++) {
			_font->draw(_textMessages[i].message,irr::core::rect<irr::s32>(130,10+(i*35),300,50+(i*35)),_colour);
		}
	}
}