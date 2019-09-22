
#include "fbx_loader.h"

using namespace Fbx;

const int TRIANGLE_VERTEX_COUNT = 3;
const int VERTEX_STRIDE = 4;
const int NORMAL_STRIDE = 3;
const int UV_STRIDE = 2;

FbxLoader::FbxLoader()
{
}

void FbxLoader::InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene)
{
	//The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
	pManager = FbxManager::Create();
	if (!pManager)
	{
		FBXSDK_printf("Error: Unable to create FBX Manager!\n");
		exit(1);
	}
	else FBXSDK_printf("Autodesk FBX SDK version %s\n", pManager->GetVersion());

	//Create an IOSettings object. This object holds all import/export settings.
	FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
	pManager->SetIOSettings(ios);

	//Load plugins from the executable directory (optional)
	FbxString lPath = FbxGetApplicationDirectory();
	pManager->LoadPluginsDirectory(lPath.Buffer());

	//Create an FBX scene. This object holds most objects imported/exported from/to files.
	pScene = FbxScene::Create(pManager, "My Scene");
	if (!pScene)
	{
		FBXSDK_printf("Error: Unable to create FBX scene!\n");
		exit(1);
	}
}

bool FbxLoader::LoadFile()
{
	bool lResult = false;
	if (mImporter->Import(mScene) == true)
	{
		// Check the scene integrity!
		FbxStatus status;
		FbxArray< FbxString*> details;
		FbxSceneCheckUtility sceneCheck(mScene, &status, &details);
		lResult = sceneCheck.Validate(FbxSceneCheckUtility::eCkeckData);
		if (lResult == false)
		{
			if (details.GetCount())
			{
				FBXSDK_printf("Scene integrity verification failed with the following errors:\n");

				for (int i = 0; i < details.GetCount(); i++)
					FBXSDK_printf("   %s\n", details[i]->Buffer());

				FbxArrayDelete<FbxString*>(details);
			}
		}
		if (lResult)
		{
			// Convert Axis System to what is used in this example, if needed
			FbxAxisSystem SceneAxisSystem = mScene->GetGlobalSettings().GetAxisSystem();
			FbxAxisSystem OurAxisSystem(FbxAxisSystem::eYAxis, FbxAxisSystem::eParityOdd, FbxAxisSystem::eRightHanded);
			if (SceneAxisSystem != OurAxisSystem)
			{
				OurAxisSystem.ConvertScene(mScene);
			}

			// Convert Unit System to what is used in this example, if needed
			FbxSystemUnit SceneSystemUnit = mScene->GetGlobalSettings().GetSystemUnit();
			if (SceneSystemUnit.GetScaleFactor() != 1.0)
			{
				//The unit in this example is centimeter.
				//SceneSystemUnit.ConvertScene(mScene, SceneSystemUnit.DefaultConversionOptions);
			}
			FbxGeometryConverter lGeomConverter(mSdkManager);
			lGeomConverter.Triangulate(mScene, /*replace*/true);
		}
    }
    mImporter->Destroy();
    mImporter = nullptr;
	return true;
}

void Fbx::FbxLoader::Initialize()
{
    InitializeSdkObjects(mSdkManager, mScene);
    if (mSdkManager)
    {
        // Create the importer.
        int lFileFormat = -1;
        mImporter = FbxImporter::Create(mSdkManager, "");
        if (!mSdkManager->GetIOPluginRegistry()->DetectReaderFileFormat(fileName, lFileFormat))
        {
            // Unrecognizable file format. Try to fall back to FbxImporter::eFBX_BINARY
            lFileFormat = mSdkManager->GetIOPluginRegistry()->FindReaderIDByDescription("FBX binary (*.fbx)");;
        }
        // Initialize the importer by providing a filename.
        if (mImporter->Initialize(fileName, lFileFormat) == true)
            FBXSDK_printf("Importer Initialize Success!\n");
    }
}

void Fbx::FbxLoader::SetFile(const char* file)
{
	strcpy(fileName, file);
}

void RecursiveNode(void * pModel, void* pNode)
{

}

void CalcModelNode(void * pModel)
{

}

void* Fbx::FbxLoader::SaveXmodFile()
{
	return 0;
}

int GetMeshNodeCount(FbxNode* pNode)
{
	int count = 0;
	const int childCount = pNode->GetChildCount();
	for (int i = 0; i < childCount; ++i)
	{
		FbxNode* child = pNode->GetChild(i);

		FbxNodeAttribute* pNodeAttribute = child->GetNodeAttribute();
		if (pNodeAttribute && pNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
			count++;
	}
	return count;
}

void Fbx::FbxLoader::SaveNodeRecursive(FbxNode* pNode, void* modelNode)
{
}

void Fbx::FbxLoader::SaveNode(FbxNode* pNode, void* modelNode)
{
	FbxNodeAttribute* pNodeAttribute = pNode->GetNodeAttribute();
	if (pNodeAttribute)
	{
		if (pNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			SaveNodeMesh(pNode, modelNode);
		}
	}
}

void Fbx::FbxLoader::SaveNodeMesh(FbxNode* pNode, void* modelNode)
{

}

