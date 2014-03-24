#pragma once
#include "Message.h"
#include <queue>

namespace GameEngine{
	/*! \brief Queues and dispatches messages
	 *  \ingroup  Engine
	 */
	class MessageHandler
	{
		private:
			//! Constructor.
			MessageHandler(){}

			//! queue of messages.
			static std::queue<Message> _messages;
		public:
			//! Destructor
			~MessageHandler();

			//! Process message queue.
			static bool update();

			//! Queue a new message to be sent.
			static void sendMessage(const Message& message);
	};
}