
#ifndef _SCENE_CONTEXT_H
#define _SCENE_CONTEXT_H

#include "fbx_header.h"
#include "../mesh/mesh.h"

const int FileNameLen = 64;

namespace Fbx
{
	class FbxLoader
	{
	public:
		FbxManager * mSdkManager;
		FbxScene * mScene;
		FbxImporter * mImporter;
    char fileName[FileNameLen];
    void* mModel;
	public:
		// Initialize with a .FBX, .DAE or .OBJ file name and current window size.
		FbxLoader();
		void InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene);
		bool LoadFile();
        void Initialize();
		void SetFile(const char* file);
		void* SaveXmodFile();
		void SaveNodeRecursive(FbxNode* pNode, void* modelNode);
		void SaveNode(FbxNode* pNode, void* modelNode);
		void SaveNodeMesh(FbxNode* pNode, void* modelNode);
	};

}

#endif