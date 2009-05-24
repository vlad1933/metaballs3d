#pragma once

#include "Common.h"
#include "ScalarField3D.h"

//-----------------------------------
// PlaneField
//-----------------------------------

class PlaneField : public ScalarField3D
{
public:
	PlaneField(Vector3 axis, float origin);
	virtual ~PlaneField();

	void SetAxis(Vector3 axis) { m_axis = axis; }
	void SetOrigin(float origin) { m_origin = origin; }

	virtual ScalarFieldValue Sample(const Vector3& position) const override;

private:
	Vector3 m_axis;
	float m_origin;
};
