#include "SphericalField.h"

//-----------------------------------
// SphericalField
//-----------------------------------

SphericalField::SphericalField(const Vector3& center, float radius)
: m_center(center), m_radiusSquared(radius * radius), m_radius(radius)
{
}

SphericalField::~SphericalField()
{
}

FieldValue SphericalField::Sample(const Vector3& position) const 
{
	FieldValue result;
	Vector3 relativePos = position - m_center;
	float length = relativePos.length();
	float lengthSquared = length * length;

	result.Scalar = m_radiusSquared / lengthSquared;
	result.Gradient =  m_radiusSquared / (lengthSquared * length) * relativePos;
	result.Color = m_color;

	return result;
}