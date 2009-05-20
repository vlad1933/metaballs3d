#include "ExampleApplication.h"

#include "Common.h"
#include "DynamicMesh.h"

// Declare a subclass of the ExampleFrameListener class
class MyListener : public ExampleFrameListener
{
public:
	MyListener(RenderWindow* win, Camera* cam) : ExampleFrameListener(win, cam)
	{
	}

	bool frameStarted(const FrameEvent& evt)
	{
		return ExampleFrameListener::frameStarted(evt);        
	}

	bool frameEnded(const FrameEvent& evt)
	{
		return ExampleFrameListener::frameEnded(evt);        
	}
};

// Declare a subclass of the ExampleApplication class
class SampleApp : public ExampleApplication 
{
public:
	SampleApp() 
	{
	}

protected:
	// Define what is in the scene
	void createScene(void)
	{
		mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );

		SceneNode *node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode( "MeshNode" );		

		DynamicMesh* mesh = new DynamicMesh("MyMesh");
		mesh->BeginMesh();

		mesh->AddVertex(Vector3(100,0,0), Vector3(0,0,0), ColourValue(1,0,0));
		mesh->AddVertex(Vector3(0,100,0), Vector3(0,0,0), ColourValue(1,0,0));
		mesh->AddVertex(Vector3(0,0,100), Vector3(0,0,0), ColourValue(1,0,0));

		mesh->AddVertex(Vector3(-100,0,0), Vector3(0,0,0), ColourValue(0,1,0));

		mesh->AddTriangle(0,1,2);
		mesh->AddTriangle(3,2,1);

		mesh->EndMesh();

		node1->attachObject( mesh );
	}

	// Create new frame listener
	void createFrameListener(void)
	{
		mFrameListener = new MyListener(mWindow, mCamera);
		mRoot->addFrameListener(mFrameListener);
	}
};

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
#define WIN32_LEAN_AND_MEAN 
#include "windows.h" 
	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT) 
#else 
	int main(int argc, char **argv) 
#endif 
	{
		// Instantiate our subclass
		SampleApp myApp;

		try {
			// ExampleApplication provides a go method, which starts the rendering.
			myApp.go();
		}
		catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
			MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "Exception:\n";
			std::cerr << e.getFullDescription().c_str() << "\n";
#endif
			return 1;
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif
