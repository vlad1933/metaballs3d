#include "RuleManager.h"

// ------------------------------------
// RuleManager
// ------------------------------------

RuleManager::RuleManager(void)
{
}

RuleManager::~RuleManager(void)
{
}

const Rule& RuleManager::CreateRule(std::string name)
{
	Rule rule;
	m_rules.push_back(rule);

	return *(m_rules.end()-1);
}

const Rule& RuleManager::GetRuleByName(const std::string& name) const
{
}
