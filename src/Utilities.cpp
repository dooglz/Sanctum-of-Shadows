#include "Utilities.h"

namespace GameEngine{
	//UI -------------------------------------------
	//static init
	irr::gui::CGUITTFont* UI::_font;
	irr::IrrlichtDevice* UI::_device;
	irr::video::SColor UI::_colour;
	std::vector<UI::TextMessage> UI::_textMessages;

	UI::UI(irr::IrrlichtDevice* dev){
		_device = dev;
		//_font = _device->getGUIEnvironment()->getBuiltInFont();
		_colour = irr::video::SColor(255,255,255,255);

		/*
		 *	Load TrueType Font to CGUITTFace
		 */
		irr::gui::IGUIEnvironment* env = dev->getGUIEnvironment();
		_font =  irr::gui::CGUITTFont::createTTFont(env, "fonts/kochi-gothic-subst.ttf", 30);
		// Set the font.
		irr::gui::IGUISkin* skin = env->getSkin();
		skin->setFont(_font);
 
	}

	UI::~UI()
	{
		_font->drop();
	}
	
	void UI::displayTextMessage(const std::string& message, const unsigned int time){
		TextMessage m;
		m.message = message;
		m.timeLeft = time;
		_textMessages.push_back(m);
	}
	void UI::update(){
		for (auto & message : _textMessages) {
			//Do domething
		}
	}
	void UI::render(){
		for (auto & message : _textMessages) {
			//Do domething
		}
		
		_font->draw(
			L"I Spent 7 Fucking Hours Getting this text To Render",
            irr::core::rect<irr::s32>(130,10,300,50),_colour
		);
	}

	// -------------------------------------------
}