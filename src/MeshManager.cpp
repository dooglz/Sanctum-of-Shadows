#include "MeshManager.h"

namespace GameEngine{

	void MeshManager::analyse(irr::scene::IMesh* mesh, bool deepscan)
	{
		std::cout << "mesh->getMeshBufferCount: " << mesh->getMeshBufferCount() <<std::endl;
		for(unsigned int i = 0; i< mesh->getMeshBufferCount(); i++)
		{
			std::cout << "   MeshBuffer("<< i
				<<")\tVertex Count: " << mesh->getMeshBuffer(i)->getVertexCount()
				<<" Type: " << mesh->getMeshBuffer(i)->getVertexType()
				<<" Index Count: " << mesh->getMeshBuffer(i)->getIndexCount()
				<<" Type: " << mesh->getMeshBuffer(i)->getIndexType()
				<<std::endl;
		}
		
		if(deepscan)
		{
			irr::scene::IMeshBuffer* mb  =mesh->getMeshBuffer(0);
			
			irr::u16* mb_indices = mb->getIndices();
			std::cout << "Indices" << std::endl;
			for(unsigned int j=0; j< mb->getIndexCount();j++){
				// scale the indices from multiple meshbuffers to single index array
				std::cout <<"\t"<< j <<": "<< mb_indices[j];
			}

			if(mb->getVertexType()==irr::video::EVT_STANDARD)
			{
				std::cout << "EVT_STANDARD verticies" << std::endl;
			   irr::video::S3DVertex* mb_vertices=(irr::video::S3DVertex*)mb->getVertices();
			   for(unsigned int j=0;j < mb->getVertexCount();j++){
				   std::cout << j <<": "<< mb_vertices[j].Pos.X<<", "<<mb_vertices[j].Pos.Y<<", "<<mb_vertices[j].Pos.Z<<", "<<std::endl;
			   } 
			}
			else if(mb->getVertexType()==irr::video::EVT_2TCOORDS)
			{
				std::cout << "EVT_2TCOORDS verticies" << std::endl;
				irr::video::S3DVertex2TCoords* mb_vertices=(irr::video::S3DVertex2TCoords*)mb->getVertices();
				for(unsigned int j=0;j < mb->getVertexCount();j++){
					std::cout << j <<": "<< mb_vertices[j].Pos.X<<", "<<mb_vertices[j].Pos.Y<<", "<<mb_vertices[j].Pos.Z<<", "<<std::endl;
				}    
			 }
			//irr::video::S3DVertex2TCoords[]* vtx = (irr::video::S3DVertex2TCoords[]*)mesh->getMeshBuffer(0)->getVertices();
			//std::cout << " X: " << vtx->Pos.X << " Y: " << vtx->Pos.Y<< " Z: " << vtx->Pos.Z <<std::endl;
		}
		//
	}   
	void MeshManager::analyseI(irr::scene::IAnimatedMesh* mesh, bool deepscan)
	{
		std::cout << "Animated mesh->getMeshBufferCount: " << mesh->getMeshBufferCount()<<" analyising only first frame, " <<std::endl;
		analyse(mesh->getMesh(0),deepscan);
	}

	/*
	static btBvhTriangleMeshShape* convertToBulletTriangleMesh(irr::scene::IMesh* mesh){
		
		btStridingMeshInterface* stridingMesh;
		stridingMesh->
		btBvhTriangleMeshShape* shape = new btBvhTriangleMeshShape(stridingMesh,false,true);
		return shape;
	}
	*/

	btBvhTriangleMeshShape* MeshManager::convertToBulletTriangleMesh(irr::scene::IMesh* mesh){
		unsigned int i,j;
		int numTriangles = 0; //this is the count of traingles,  = indices / 3
		int* indices;
		int triangleIndexStride = sizeof(int) * 3;
		int numVerticies =0;
		btScalar* vertices;
		int vertStride = sizeof(btScalar) * 3;

		std::cout << "converting mesh" << std::endl;

		// count vertices and indices
		for(i=0;i < mesh->getMeshBufferCount();i++)
		{
		  irr::scene::IMeshBuffer* mb=mesh->getMeshBuffer(i);
		  numTriangles+=mb->getIndexCount();
		  numVerticies+=mb->getVertexCount();
		}
		std::cout << "numTriangles: " << numTriangles << " numVerticies: " << numVerticies << std::endl;

		// build structure for trimesh geom
		vertices = new btScalar[numVerticies*3];
		indices = new int[numTriangles];
		
		// fill trimesh geom
		int ci=0; // current index in the indices array
		int cif=0; // offset of the irrlicht-vertex-index in the vetices array 
		int cv=0; // current index in the vertices array
		for(i=0; i < mesh->getMeshBufferCount(); i++)
		{
			irr::scene::IMeshBuffer* mb=mesh->getMeshBuffer(i);
			
			//Indices
			irr::u16* mb_indices = mb->getIndices();
			for(j=0; j < mb->getIndexCount(); j++)
			{
				// scale the indices from multiple meshbuffers to single index array
				//indices[ci]=cif+mb_indices[j];
				indices[ci]=mb_indices[j];
			//	indices[ci+cif]=mb_indices[j];
			//	std::cout << ci << " " << indices[ci] << std::endl;

				ci++;
			}
			// update the offset for the next meshbuffer
			cif=cif+mb->getVertexCount();

			// fill vertices
			if(mb->getVertexType()==irr::video::EVT_STANDARD)
			{
				irr::video::S3DVertex* mb_vertices= (irr::video::S3DVertex*)mb->getVertices();
				
				for(j=0;j<mb->getVertexCount();j++)
				{
					vertices[cv] = mb_vertices[j].Pos.X;
					vertices[cv+1] = mb_vertices[j].Pos.X;
					vertices[cv+2] = mb_vertices[j].Pos.X;
					//std::cout << cv << " " << vertices[cv] << std::endl;
					cv += 3;
				} 
			//	std::cout << std::endl;
			}
			else if(mb->getVertexType()==irr::video::EVT_2TCOORDS)
			{
				irr::video::S3DVertex2TCoords* mb_vertices=
				(irr::video::S3DVertex2TCoords*)mb->getVertices();
				for(j=0;j<mb->getVertexCount();j++)
				{
					vertices[cv] = mb_vertices[j].Pos.X;
					vertices[cv+1] = mb_vertices[j].Pos.X;
					vertices[cv+2] = mb_vertices[j].Pos.X;
				//	std::cout << cv << " " << vertices[cv] << std::endl;
					cv += 3;
				}    
			//	std::cout << std::endl;
			}
		}
		
		btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray(
			//number of Triangles	
			numTriangles/3,
			//the array of vertex indices that makes up the triangles
			indices,
			//number of bytes to skip in the vertex indices array from the start of one triangle to the start of the next triangle.
			triangleIndexStride,
			//number of vertices
			(numVerticies*3),
			//the array of vertex positions
			vertices,
			//number of bytes to skip in the vertex position array from the start of one vertex to the start of the next vertex.
			vertStride
		);
		
		btTriangleIndexVertexArray* meshInterface2 = new btTriangleIndexVertexArray();
		btIndexedMesh part;
		part.m_vertexBase = (const unsigned char*)vertices;
		part.m_vertexStride = vertStride;
		part.m_numVertices = (numVerticies*3);
		part.m_triangleIndexBase = (const unsigned char*)indices;
		part.m_triangleIndexStride = triangleIndexStride;
		part.m_numTriangles = (numTriangles / 3);
		//part.m_indexType = PHY_SHORT;

		std::cout << "vertstride: " << vertStride << "\t(numVerticies*3): " << (numVerticies*3) << std::endl;
		std::cout << "triangleIndexStride: " << triangleIndexStride << "\t(numTriangles / 3): " << (numTriangles / 3) << std::endl;
		std::cout << "vertices[0]: " << vertices[0] << "\tindices[0]: " << indices[0] << std::endl;
		std::cout << "(const unsigned char*)vertices[0]: " << ((const unsigned char*)vertices)[0] << std::endl;
		std::cout << "sizeof(vertices): " << sizeof(vertices) << "\tsizeof((const unsigned char*)vertices): " << sizeof((const unsigned char*)vertices) << std::endl;

		meshInterface->addIndexedMesh(part,PHY_SHORT);

		btBvhTriangleMeshShape* shape = new btBvhTriangleMeshShape(meshInterface,true,true);
		//shape->setLocalScaling(btVector3(100.0f,100.0f,100.0f));
		//shape->isInfinite();
		return shape;
	}

}