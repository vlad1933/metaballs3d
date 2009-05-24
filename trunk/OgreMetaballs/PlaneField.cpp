#include "PlaneField.h"

//-----------------------------------
// PlaneField
//-----------------------------------

PlaneField::PlaneField(Vector3 axis, float origin)
{
	m_axis = axis;
	m_axis.normalise();

	m_origin = origin;
}

PlaneField::~PlaneField()
{
}

ScalarFieldValue PlaneField::Sample(const Vector3& position) const
{
	ScalarFieldValue result;

	Vector3 relativePos = position - m_origin * m_axis;

	result.Scalar = relativePos.dotProduct(m_axis)+1;
	result.Gradient = m_axis;
	result.Color = m_color;

	return result;
}