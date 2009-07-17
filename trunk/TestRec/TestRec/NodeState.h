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

public:
	Matrix4x4 m_transform;
	ColorHSV m_color;
	float m_other[4];
};
