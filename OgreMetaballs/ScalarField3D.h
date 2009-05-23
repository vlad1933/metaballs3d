#pragma once

#include "Common.h"

struct FieldValue
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

	virtual FieldValue Sample(const Vector3& position) const = 0;
};
