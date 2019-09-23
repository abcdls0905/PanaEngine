#include "fbxinterface.h"
#include "../mesh/mesh.h"
#include "fbx_loader.h"

using namespace Fbx;

Mesh* FbxInterface::Import(const char *file)
{
	FbxLoader fbx_loader;
	fbx_loader.SetFile("");
	fbx_loader.Initialize();
	fbx_loader.LoadFile();
	fbx_loader.SaveXmodFile();
	Mesh* mesh = new Mesh;
	return mesh;
}
