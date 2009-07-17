#include "Transform.h"

Transform::Transform(void)
{
    m_other[0] = 0;
}

Transform::Transform(float test)
{
    m_other[0] = test;
}

Transform::~Transform(void)
{
}

NodeState Transform::Apply(const NodeState& state) const
{
	NodeState newState = state;
	newState.m_other[0] += m_other[0];
	return newState;
}
