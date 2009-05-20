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

	virtual float Value(Vector3 position) = 0;
	virtual Vector3 Gradient(Vector3 v) = 0;
};
