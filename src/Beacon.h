#pragma once
#include "PhysicalEntity.h"

/*! \brief A Beacon, can be lit, doesn't move. 
 * \ingroup Game
 */
class Beacon : public GameEngine::Entity{

	private:

		//! Radius of light, when lit.
		static const unsigned int _lightRange = 500;

		//! Radius of player healing, when lit.
		static const unsigned int _healingRange = 150;

		//! Status of the beacon.
		bool _isLit;

		//! Vector of cool effects to enable when lit.
		std::vector<irr::scene::ISceneNode*> _effects;

		//! The light scene node
		irr::scene::ILightSceneNode* _light;

		//! The bullet Rigidbody for the beacon.
		btRigidBody* _rigidBody;

	public:

		//! Constructor.
		Beacon (const irr::core::vector3df& position);

		//! Destructor.
		~Beacon (){};

		//! Toggle state, lights and effects.
		void light(bool onOff);

		//! returns _isLit.
		bool isLit(){
			return _isLit;
		}

		//! Check player location, turn on, Heal player.
		void update(float delta);

		void handleMessage(const GameEngine::Message& message);

		void intitalise();

		bool loadContent();
};