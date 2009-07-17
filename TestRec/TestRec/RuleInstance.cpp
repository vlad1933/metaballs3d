#include "RuleInstance.h"

RuleInstance::RuleInstance(Rule* rule, float weight) : m_rule(rule), m_weight(weight)
{
}

RuleInstance::~RuleInstance(void)
{
}

void RuleInstance::AddChild(Rule* rule, Transform transform)
{
	m_childs.push_back(Child(rule, transform));
}
