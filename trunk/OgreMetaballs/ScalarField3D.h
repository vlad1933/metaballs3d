#pragma once

#include "Common.h"

//-----------------------------------
// ScalarField3D
//-----------------------------------

class ScalarField3D
{
public:
	ScalarField3D();
	virtual ~ScalarField3D();

	virtual float Value(const Vector3& position) const = 0;
	virtual Vector3 Gradient(const Vector3& v) const = 0;
};
