#pragma once

#include "Common.h"
#include "ExampleApplication.h"

//-----------------------------------
// Forward declarations
//-----------------------------------

class DynamicMesh;
class ScalarField3D;
class SphericalField;
class MultiScalarField;
class MarchingCubes;

//-----------------------------------
// MetaballsFrameListener
//-----------------------------------

class MetaballsFrameListener : public ExampleFrameListener
{
public:
	MetaballsFrameListener(RenderWindow* win, Camera* cam, DynamicMesh* meshBuilder);
	~MetaballsFrameListener(void);

protected:
	virtual void moveCamera() override;

	bool frameStarted(const FrameEvent& evt) override;
	bool frameEnded(const FrameEvent& evt) override;

	void UpdateFields();

private:
	DynamicMesh* m_meshBuilder;
	MultiScalarField* m_finalField;
	SphericalField* m_field1;
	SphericalField* m_field2;
	MarchingCubes* m_marchingCube;

	float m_totalTime;

	Ogre::Radian m_camAzimuth, m_camPolar;
	float m_camRadius;
};
