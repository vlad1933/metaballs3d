#include "Transform.h"

Transform::Transform(void)
{
}

Transform::~Transform(void)
{
}

NodeState Transform::Apply(const NodeState& state) const
{
	NodeState newState = state;
	// modify the state
	return newState;
}
