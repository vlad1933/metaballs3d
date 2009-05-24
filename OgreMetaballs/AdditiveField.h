#pragma once
#include "ScalarField3D.h"

//-----------------------------------
// AdditiveField
//-----------------------------------

class AdditiveField :
	public ScalarField3D
{
public:
	AdditiveField(ScalarField3D* field1,ScalarField3D* field2);
	virtual ~AdditiveField();

	virtual ScalarFieldValue Sample(const Vector3& position) const override;

private:
	ScalarField3D* m_field1;
	ScalarField3D* m_field2;
};
