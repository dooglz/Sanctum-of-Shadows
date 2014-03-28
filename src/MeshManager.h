#pragma once
#include <irrlicht.h>
#include <iostream>
#include <btBulletCollisionCommon.h>

namespace GameEngine{
	/*! \brief Converts Irrlicht mesh data to bullet btBvhTriangleMeshShapes.
	 *  \ingroup  Engine
	 */
	class MeshManager
	{
	private:
		MeshManager(){}
	public:
		~MeshManager();

		//! print info about a mesh.
		static void analyse(irr::scene::IMesh* mesh, bool deepscan);

		//! print info about an animated mesh.
		static void analyseI(irr::scene::IAnimatedMesh* mesh, bool deepscan);

		//! Converts Irrlicht mesh data to bullet btBvhTriangleMeshShapes.
		static btBvhTriangleMeshShape* convertToBulletTriangleMesh(irr::scene::IMesh* mesh);
	};
}