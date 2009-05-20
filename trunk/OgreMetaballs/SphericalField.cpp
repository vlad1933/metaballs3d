#include "SphericalField.h"

SphericalField::SphericalField(const Vector3& center, float radius)
: m_center(center), m_radiusSquared(radius * radius), m_radius(radius)
{
}

SphericalField::~SphericalField()
{
}

float SphericalField::Value(const Vector3 &position) const
{
	return m_radiusSquared / (m_center - position).squaredLength();
}

Vector3 SphericalField::Gradient(const Vector3 &position) const
{
	Vector3 diff = position - m_center;
	float length = diff.length();
	return m_radiusSquared / (length * length * length) * diff;
}