#include <irrlicht.h>
#include <iostream>
#include <btBulletCollisionCommon.h>

namespace GameEngine{

	class MeshManager
	{
	private:
		MeshManager(){}
	public:
		~MeshManager();
		static void analyse(irr::scene::IMesh* mesh, bool deepscan);
		static void analyseI(irr::scene::IAnimatedMesh* mesh, bool deepscan);
		static btBvhTriangleMeshShape* convertToBulletTriangleMesh(irr::scene::IMesh* mesh);
	};
}