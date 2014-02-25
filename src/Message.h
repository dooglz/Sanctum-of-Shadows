#pragma once
#include <string>

namespace GameEngine{

	//forward declaration
	class Entity;

	struct Message {
		Entity* entity;
		//TODO make this an enum
		std::string message;
		void* data;
		Message(Entity* target, const std::string& message, void* data)
			:entity(target), message(message), data(data)
		{
		}
	} ;
}