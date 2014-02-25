#include "MessageHandler.h"
#include "Entity.h"

//TODO make all messages an enum.
namespace GameEngine{
	std::queue<Message> MessageHandler::_messages = std::queue<Message>();

	MessageHandler::~MessageHandler()
	{
		while(!_messages.empty())
		{
			_messages.pop();
		}
	}
	bool MessageHandler::initialise()
	{
		//TODO
		return true;
	}
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

	void MessageHandler::sendMessage(const Message& message)
	{
		_messages.push(message);
	}                
}