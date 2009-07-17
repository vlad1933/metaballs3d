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

Rule* RuleManager::CreateRule(const std::string& name)
{
    Rule* rule = new Rule(name);
	m_rules.push_back(rule);
	return rule;
}

Rule* RuleManager::GetRuleByName(const std::string& name)
{
    for(size_t i=0; i<m_rules.size();i++)
    {
        if(m_rules[i]->GetName() == name)
        {
            return m_rules[i];
        }
    }
    return NULL;
}
