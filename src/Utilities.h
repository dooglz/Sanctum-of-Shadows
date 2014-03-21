#include <irrlicht.h>
#include <string>
#include <vector>
#include "CGUITTFont.h"

namespace GameEngine{

	class UI{

	public:
		struct TextMessage {
		  std::string message;
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
		static void displayTextMessage(const std::string& message,const unsigned int time);
		//We don't care about time inbetween frames atm
		//TODO make text messages time based
		static void update();
		static void render();
		
	};

}