#pragma once
#include "PhysicalEntity.h"

class Beacon : public GameEngine::Entity{
private:
	int _range;
	bool _isLit;
	irr::scene::ILightSceneNode* _light;
public:
	Beacon (const irr::core::vector3df& position);
	~Beacon (){};
	void intitalise();
	bool loadContent();
	void unloadContent(){};
	void update(float delta);
	//
	void handleMessage(const GameEngine::Message& message);
};