#include "SanctumOfShadows.h"

bool SanctumOfShadows::init(){
	std::wcout <<  _gameTitle << " Game code init" << std::endl;
	//
	if (!GameEngine::engine.loadContent()){
		return false;
	}
	return true;
}

bool SanctumOfShadows::update(float delta){

	//TODO, move some of this to baseclass
	if(GameEngine::handler.keyDown(irr::KEY_F1)){
		GameEngine::engine.debug();
	}
	return true;
}

void SanctumOfShadows::reset(){

}
