#include <irrlicht.h>
#include <iostream>

namespace GameEngine{

	class MeshManager
	{
	private:
		MeshManager(){}
	public:
		~MeshManager();
		static void analyse(irr::scene::IMesh* mesh, bool deepscan);
		static void analyseI(irr::scene::IAnimatedMesh* mesh, bool deepscan);
	};
}