#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

namespace GameEngine{
	class Physics{

	private:
		static btDefaultCollisionConfiguration* _collisionConfig;
		static btCollisionDispatcher* _dispatcher;
		static btBroadphaseInterface* _broadPhase;
		static btSequentialImpulseConstraintSolver* _solver;
	public:
		static btDiscreteDynamicsWorld* world;
		static bool initialise();
		static void shutdown();
	};
}