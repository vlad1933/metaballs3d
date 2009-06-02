#pragma once

#include "Common.h"
#include "ScalarField3D.h"

//-----------------------------------
// SphericalField
//-----------------------------------

class SphericalField : public ScalarField3D
{
public:
	SphericalField(const Vector3& center, float radius);
	virtual ~SphericalField();

	virtual float Scalar(const Vector3& position) const override;
	virtual Vector3 Gradient(const Vector3& position) const override;
	virtual ColourValue Color(const Vector3& position) const override;

	void SetCenter(Vector3 center) { m_center = center; }
	void SetRadius(float r) { m_radius = r; m_radiusSquared = r*r; }

private:
	float m_radius;
	float m_radiusSquared;
	Vector3 m_center;
};
