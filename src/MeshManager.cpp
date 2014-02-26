#include "MeshManager.h"

namespace GameEngine{

	void MeshManager::analyse(irr::scene::IMesh* mesh, bool deepscan)
	{
		std::cout << "mesh->getMeshBufferCount: " << mesh->getMeshBufferCount() <<std::endl;
		for(int i = 0; i< mesh->getMeshBufferCount(); i++)
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
			for(int j=0; j< mb->getIndexCount();j++){
				// scale the indices from multiple meshbuffers to single index array
				std::cout <<"\t"<< j <<": "<< mb_indices[j];
			}

			if(mb->getVertexType()==irr::video::EVT_STANDARD)
			{
				std::cout << "EVT_STANDARD verticies" << std::endl;
			   irr::video::S3DVertex* mb_vertices=(irr::video::S3DVertex*)mb->getVertices();
			   for(int j=0;j < mb->getVertexCount();j++){
				   std::cout << j <<": "<< mb_vertices[j].Pos.X<<", "<<mb_vertices[j].Pos.Y<<", "<<mb_vertices[j].Pos.Z<<", "<<std::endl;
			   } 
			}
			else if(mb->getVertexType()==irr::video::EVT_2TCOORDS)
			{
				std::cout << "EVT_2TCOORDS verticies" << std::endl;
				irr::video::S3DVertex2TCoords* mb_vertices=(irr::video::S3DVertex2TCoords*)mb->getVertices();
				for(int j=0;j < mb->getVertexCount();j++){
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
}