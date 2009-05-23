#pragma once
#include "ScalarField3D.h"

//-----------------------------------
// MultiScalarField
//-----------------------------------

class MultiScalarField :
	public ScalarField3D
{
public:
	MultiScalarField(ScalarField3D* field1,ScalarField3D* field2);
	~MultiScalarField();

	virtual ScalarFieldValue Sample(const Vector3& position) const override;

private:
	ScalarField3D* m_field1;
	ScalarField3D* m_field2;
};
