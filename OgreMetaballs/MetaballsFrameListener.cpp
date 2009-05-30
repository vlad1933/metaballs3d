#include "MetaballsFrameListener.h"

#include "DynamicMesh.h"
#include "MarchingCubesImpl.h"
#include "ScalarField3D.h"
#include "TorusScene.h"
#include "PlaneScene.h"
#include "HeartScene.h"

//-----------------------------------
// MetaballsFrameListener
//-----------------------------------

MetaballsFrameListener::MetaballsFrameListener(RenderWindow* win, Camera* cam, DynamicMesh* meshBuilder) : ExampleFrameListener(win, cam)
{
	m_totalTime = 0;

	m_meshBuilder = meshBuilder;

	m_scene = new TorusScene();

	m_scene->CreateFields();

	//Create the object responsible for the mesh creation
	m_marchingCube = new MarchingCubesImpl(m_meshBuilder);
	m_marchingCube->SetScalarField(m_scene->GetScalarField());
	m_marchingCube->Initialize(m_scene->GetSceneSize(), m_scene->GetSpaceResolution(), 1);

	//Initialize the camera coordinates
	m_camAzimuth = 0;
	m_camPolar = 0;
	m_camRadius = 120 * m_scene->GetSceneSize();
}

MetaballsFrameListener::~MetaballsFrameListener(void)
{
}

void MetaballsFrameListener::moveCamera()
{
	//Change the camera coordinates according to the mouse input
	m_camAzimuth += mRotX;
	m_camPolar += mRotY;

	//Block the camera over the poles
	const Ogre::Radian maxPolarAngle = Ogre::Radian(Ogre::Math::HALF_PI) - Radian(0.01f);
	if(m_camPolar > maxPolarAngle)
		m_camPolar = maxPolarAngle;
	if(m_camPolar < -maxPolarAngle)
		m_camPolar = -maxPolarAngle;

	//Compute the new camera position using spherical coordinates
	Vector3 camPos = m_camRadius * Vector3(
		Ogre::Math::Cos(m_camAzimuth) * Ogre::Math::Cos(m_camPolar),
		Ogre::Math::Sin(m_camPolar),
		Ogre::Math::Sin(m_camAzimuth) * Ogre::Math::Cos(m_camPolar));

	mCamera->setPosition(camPos);
	mCamera->lookAt(Vector3::ZERO);
}

bool MetaballsFrameListener::frameStarted(const FrameEvent& evt)
{		
	if(!mKeyboard->isKeyDown(OIS::KC_SPACE))
	{
		m_totalTime += evt.timeSinceLastFrame;
	}

	if(mKeyboard->isKeyDown(OIS::KC_T))
	{
		mCamera->setPolygonMode(Ogre::PM_WIREFRAME);
	}
	else
	{
		mCamera->setPolygonMode(Ogre::PM_SOLID);
	} 

	m_scene->UpdateFields(m_totalTime);

	//Recreate the mesh
	m_marchingCube->CreateMesh();

	return ExampleFrameListener::frameStarted(evt);        
}

bool MetaballsFrameListener::frameEnded(const FrameEvent& evt)
{
	return ExampleFrameListener::frameEnded(evt);        
}