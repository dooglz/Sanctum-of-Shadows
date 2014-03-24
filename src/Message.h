#pragma once
#include <string>

namespace GameEngine{

	//forward declaration
	class Entity;
	/*! \brief A message to be sent to entities
	 *  \ingroup  Engine
	 */
	struct Message {
		//! The receiving Entity
		Entity* entity;

		//TODO make this an enum
		//! String Message Data
		std::string message;

		//! Message Data, of undefined type.
		void* data;

		//! Constructor.
		Message(Entity* target, const std::string& message, void* data)
			:entity(target), message(message), data(data)
		{
		}
	} ;
}