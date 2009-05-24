#pragma once

#include "Common.h"
#include "ScalarField3D.h"

//-----------------------------------
// ToroidalField
//-----------------------------------

class ToroidalField : public ScalarField3D
{
public:
	ToroidalField(const Vector3& center, float radius, float sectionRadius);
	virtual ~ToroidalField();

	virtual ScalarFieldValue Sample(const Vector3& position) const override;

	void SetSectionRadius(float r) { m_sectionRadius = r; }
	void SetRadius(float r) { m_radius = r; }

private:
	float m_radius;
	float m_sectionRadius;
	Vector3 m_center;
};