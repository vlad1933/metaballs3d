#include "RuleInstance.h"

RuleInstance::RuleInstance(void)
{
}

RuleInstance::~RuleInstance(void)
{
}

void RuleInstance::AddChild(Rule* rule, Transform transform)
{
	m_childs.push_back(Child(rule, transform));
}
