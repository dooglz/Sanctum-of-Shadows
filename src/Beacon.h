#pragma once
#include "PhysicalEntity.h"

class Beacon : public GameEngine::Entity{
private:
	unsigned int _lightRange;
	unsigned int _healingRange;
	bool _isLit;
	std::vector<irr::scene::ISceneNode*> _effects;
	irr::scene::ILightSceneNode* _light;
	btRigidBody* _rigidBody;
public:
	Beacon (const irr::core::vector3df& position);
	~Beacon (){};
	void intitalise();
	bool loadContent();
	void unloadContent(){};
	void update(float delta);
	//
	void handleMessage(const GameEngine::Message& message);
	bool isLit(){
		return _isLit;
	}
	void light(bool onOff);

};