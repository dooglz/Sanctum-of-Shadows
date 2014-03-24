#include "MessageHandler.h"
#include "Entity.h"

namespace GameEngine{
	std::queue<Message> MessageHandler::_messages = std::queue<Message>();

	MessageHandler::~MessageHandler()
	{
		while(!_messages.empty())
		{
			//message data could be on the heap, remove
			delete _messages.front().data;
			_messages.pop();
		}
	}

	//! Process message queue.
	bool MessageHandler::update()
	{
		while(!_messages.empty())
		{
			Message message = _messages.front();
			_messages.pop();
			message.entity->handleMessage(message);
			//message data could be on the heap, remove
			delete message.data;
		}
		return true;
	}

	//! Queue a new message to be sent.
	void MessageHandler::sendMessage(const Message& message)
	{
		_messages.push(message);
	}                
}