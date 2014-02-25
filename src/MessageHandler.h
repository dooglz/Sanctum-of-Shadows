#pragma once
#include "Message.h"
#include <queue>

namespace GameEngine{

	class MessageHandler
	{
	private:
		MessageHandler(){}
		static std::queue<Message> _messages;
	public:
		~MessageHandler();
		static bool initialise();
		static bool update();
		static void sendMessage(const Message& message);
	};
}