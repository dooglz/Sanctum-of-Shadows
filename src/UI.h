#include <irrlicht.h>
#include <vector>
#include "CGUITTFont.h"

namespace GameEngine{

	class UI{

	public:
		struct TextMessage {
		  irr::core::stringw message;
		  unsigned int timeLeft;
		};
	private:
		static std::vector<TextMessage> _textMessages;
		static irr::gui::CGUITTFont* _font;
		static irr::IrrlichtDevice* _device;
		//
		static irr::video::SColor _colour;
	public:
		UI() {};
		~UI();
		UI(irr::IrrlichtDevice* dev);
		//Time = amount of frames to keep text onscreen
		static void displayTextMessage(const irr::core::stringw& message,const unsigned int time);
		//We don't care about time inbetween frames atm
		//TODO make text messages time based
		static void update();
		static void render();
		
	};

}