#include "MultiScalarField.h"

//-----------------------------------
// MultiScalarField
//-----------------------------------

MultiScalarField::MultiScalarField(ScalarField3D* field1,ScalarField3D* field2)
: m_field1(field1), m_field2(field2)
{
}

MultiScalarField::~MultiScalarField()
{
}

ScalarFieldValue MultiScalarField::Sample(const Vector3& position) const 
{
	//Sample the two base fields
	const ScalarFieldValue& v1 = m_field1->Sample(position);
	const ScalarFieldValue& v2 = m_field2->Sample(position);

	ScalarFieldValue result;

	//Value and gradient are summed
	result.Scalar = v1.Scalar + v2.Scalar;
	result.Gradient = v1.Gradient + v2.Gradient;

	//The color is linearly interpolated
	float lerp = v1.Scalar / result.Scalar;
	result.Color = lerp * v1.Color + (1-lerp) * v2.Color;

	return result;
}
