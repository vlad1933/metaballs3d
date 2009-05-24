#pragma once

#include "Common.h"

//-----------------------------------
// ScalarFieldValue
//-----------------------------------

struct ScalarFieldValue
{
	float Scalar;
	Vector3 Gradient;
	ColourValue Color;
};

//-----------------------------------
// ScalarField3D
//-----------------------------------

class ScalarField3D
{
public:
	ScalarField3D();
	virtual ~ScalarField3D();

	virtual ScalarFieldValue Sample(const Vector3& position) const = 0;

	void SetColor(ColourValue color) { m_color = color; }

protected:
	ColourValue m_color;
};
