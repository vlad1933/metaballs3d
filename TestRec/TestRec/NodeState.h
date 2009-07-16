#pragma once

#include "Common.h"

// ------------------------------------
// NodeState
// ------------------------------------

class NodeState
{
public:
	NodeState(void);
	~NodeState(void);

private:
	Matrix4x4 m_transform;
	ColorHSV m_color;
	float other[4];
};
