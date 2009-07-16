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

	const Rule& CreateRule(std::string name);
	const Rule& GetRuleByName(const std::string& name) const;

private:
	std::vector<Rule> m_rules;
};
