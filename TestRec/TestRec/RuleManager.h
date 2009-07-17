#pragma once

#include "Common.h"

#include "Rule.h"

// ------------------------------------
// RuleManager
// ------------------------------------

class RuleManager
{
public:
	RuleManager(void);
	~RuleManager(void);

	Rule* CreateRule(const std::string& name);
	Rule* GetRuleByName(const std::string& name);

private:
	std::vector<Rule*> m_rules;
};
