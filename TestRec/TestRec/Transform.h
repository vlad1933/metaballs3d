#pragma once

#include "Common.h"

#include "NodeState.h"
// ------------------------------------
// Transform
// ------------------------------------

class Transform
{
public:
	Transform(void);
	~Transform(void);

	NodeState Apply(const NodeState& state) const;

private:
	Matrix4x4 m_transform;
	ColorHSV m_color;
	float other[4];
};
