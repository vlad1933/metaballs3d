#pragma once

#include "Common.h"

#include "NodeState.h"

// ------------------------------------
// Transform
// ------------------------------------

class Transform
{
public:
	Transform();
    Transform(float test);
	~Transform();

	NodeState Apply(const NodeState& state) const;

private:
	Matrix4x4 m_transform;
	ColorHSV m_color;
	float m_other[4];
};
