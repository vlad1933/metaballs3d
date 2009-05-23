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

	//Compute the relative position from the center
	Vector3 relativePos = m_center - position;

	float lengthSquared = relativePos.squaredLength();

	//The scalar value is proportional to 1/r^2
	result.Scalar = m_radiusSquared / lengthSquared;

	//The gradient is is proportional to 1/r^3 and radial to the sphere
	result.Gradient =  (result.Scalar / lengthSquared) * relativePos;

	//The color is uniform
	result.Color = m_color;

	return result;
}