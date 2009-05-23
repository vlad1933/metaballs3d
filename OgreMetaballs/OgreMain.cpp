#include "ExampleApplication.h"

#include "Common.h"
#include "DynamicMesh.h"
#include "MarchingCubes.h"
#include "ScalarField3D.h"
#include "SphericalField.h"
#include "MultiScalarField.h"

#include "OgreMath.h"

#include <math.h>

// Declare a subclass of the ExampleFrameListener class
class MyListener : public ExampleFrameListener
{
public:
	MyListener(RenderWindow* win, Camera* cam, DynamicMesh* m) : ExampleFrameListener(win, cam)
	{
		azim = 0;
		polar = 0;
		radius = 500;

		cam->setPolygonMode(Ogre::PM_WIREFRAME);

		mesh = m;
		field1 = new SphericalField(Vector3(+1.0f,0,0), 1);
		field2 = new SphericalField(Vector3(-1.0f,0,0), 1);
		field = new MultiScalarField(field1, field2);
		cubeMarcher = new MarchingCubes(mesh);

		totalTime = 0;

		cubeMarcher->SetScalarField(field);
		cubeMarcher->Initialize(5.0f, 0.15f, 1);
	}

	DynamicMesh* mesh;
	MultiScalarField* field;
	SphericalField* field1;
	SphericalField* field2;
	MarchingCubes* cubeMarcher;

	float totalTime;

	Ogre::Radian azim, polar;
	float radius;

	virtual void moveCamera() override
	{
		Vector3 camPos;
		azim += mRotX;
		polar += mRotY;
		if(polar >= Radian(Ogre::Math::HALF_PI) - Radian(0.1f))
			polar = Radian(Ogre::Math::HALF_PI) - Radian(0.1f);
		if(polar <= -Radian(Ogre::Math::HALF_PI) + Radian(0.1f))
			polar = -Radian(Ogre::Math::HALF_PI) + Radian(0.1f);
		camPos = radius * Vector3(
			Ogre::Math::Cos(azim) * Ogre::Math::Cos(polar),
			Ogre::Math::Sin(polar),
			Ogre::Math::Sin(azim) * Ogre::Math::Cos(polar));

		mCamera->setPosition(camPos);
		mCamera->lookAt(Vector3::ZERO);
	}

	bool frameStarted(const FrameEvent& evt)
	{		
		totalTime += evt.timeSinceLastFrame;

		field1->SetRadius(0.78f + 0.2f * cos( 2.4f * totalTime));
		field1->SetColor(ColourValue(1.0f,0,0));

		field2->SetRadius(0.9f + 0.25f * cos( 1.8f * totalTime));
		field2->SetColor(ColourValue(0,1.0f,0));

		cubeMarcher->CreateMesh();

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

DynamicMesh* mesh;

protected:
	// Define what is in the scene
	void createScene(void)
	{
		mSceneMgr->setAmbientLight( 0.4f * ColourValue::White );

		{
			Light* light = mSceneMgr->createLight("Light1");
			light->setType(Light::LT_DIRECTIONAL);
			light->setDirection(Vector3(-0.6f,0.3f,-0.1f));
			light->setDiffuseColour(ColourValue(.25, .62, 0));
			light->setSpecularColour(ColourValue(.25, .25, .25));
		}

		{
			Light* light = mSceneMgr->createLight("Light2");
			light->setType(Light::LT_DIRECTIONAL);
			light->setDirection(Vector3(0.2f,-0.8f,0.8f));
			light->setDiffuseColour(ColourValue(.12, .1, .5));
			light->setSpecularColour(ColourValue(.25, .25, 25.));
		}

		{
			Light* light = mSceneMgr->createLight("Light3");
			light->setType(Light::LT_DIRECTIONAL);
			light->setDirection(Vector3(1.0f,0,-0.3f));
			light->setDiffuseColour(ColourValue(.25, .45, 3.));
			light->setSpecularColour(ColourValue(.25, .25, 25.));
		}

		SceneNode *node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode( "MeshNode" );
		node1->setScale(100 * Vector3::UNIT_SCALE);

		mesh = new DynamicMesh("MyMesh");
		node1->attachObject( mesh );
	}

	// Create new frame listener
	void createFrameListener(void)
	{
		mFrameListener = new MyListener(mWindow, mCamera, mesh);
		mRoot->addFrameListener(mFrameListener);
	}
};

extern "C" {
#define WIN32_LEAN_AND_MEAN 
#include "windows.h" 
	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT) 
	{
		// Instantiate our subclass
		SampleApp myApp;
		try {
			myApp.go();
		}
		catch (Ogre::Exception& e) {
			MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
			return 1;
		}
		return 0;
	}
}
