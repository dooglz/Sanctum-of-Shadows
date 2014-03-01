#include "Player.h"

void Player::intitalise(irr::core::vector3df position){
	_physicsMesh = new Box(GameEngine::Physics::irrVec3ToBtVec3(position),irr::core::vector3df(60.0f,100.0f,60.0f),60.0f);
}

bool Player::loadContent(){
	return true;
}

void Player::unloadContent(){

}


void Player::update(float delta){

}


