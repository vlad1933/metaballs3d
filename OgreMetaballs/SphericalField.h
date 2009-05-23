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
	~SphericalField();

	virtual FieldValue Sample(const Vector3& position) const override;

	void SetRadius(float r) { m_radius = r; m_radiusSquared = r*r; }
	void SetColor(ColourValue color) { m_color = color; }

private:
	float m_radius;
	float m_radiusSquared;
	Vector3 m_center;
	ColourValue m_color;
};
