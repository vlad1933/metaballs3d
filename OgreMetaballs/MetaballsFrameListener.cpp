#include "MetaballsFrameListener.h"

#include "DynamicMesh.h"
#include "SphericalField.h"
#include "MultiScalarField.h"
#include "MarchingCubes.h"

//-----------------------------------
// MetaballsFrameListener
//-----------------------------------

MetaballsFrameListener::MetaballsFrameListener(RenderWindow* win, Camera* cam, DynamicMesh* meshBuilder) : ExampleFrameListener(win, cam)
{
	//Initialize the camera coordinates
	m_camAzimuth = 0;
	m_camPolar = 0;
	m_camRadius = 500;

	m_totalTime = 0;

	//Create the scalar fields
	m_field1 = new SphericalField(Vector3(+1.0f,0,0), 1);
	m_field2 = new SphericalField(Vector3(-1.0f,0,0), 1);
	m_finalField = new MultiScalarField(m_field1, m_field2);

	m_field1->SetColor(ColourValue(1.0f,0,0));
	m_field2->SetColor(ColourValue(0,1.0f,0));

	m_meshBuilder = meshBuilder;

	//Create the object responsible for the mesh creation
	m_marchingCube = new MarchingCubes(m_meshBuilder);
	m_marchingCube->SetScalarField(m_finalField);
	m_marchingCube->Initialize(5.0f, 0.15f, 1);
}

MetaballsFrameListener::~MetaballsFrameListener(void)
{
}

void MetaballsFrameListener::moveCamera()
{
	//Change the camera coordinates according to the mouse inout
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


	if(mKeyboard->isKeyDown(OIS::KC_SPACE))
	{
	}
	else
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

	UpdateFields();

	//Recreate the mesh
	m_marchingCube->CreateMesh();

	return ExampleFrameListener::frameStarted(evt);        
}

bool MetaballsFrameListener::frameEnded(const FrameEvent& evt)
{
	return ExampleFrameListener::frameEnded(evt);        
}

void MetaballsFrameListener::UpdateFields()
{
	//Update the fields over time
	m_field1->SetRadius(0.78f + 0.2f * cos( 2.4f * m_totalTime));
	m_field2->SetRadius(0.9f + 0.25f * cos( 1.8f * m_totalTime));

}