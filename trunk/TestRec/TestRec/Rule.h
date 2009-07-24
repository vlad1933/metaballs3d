#pragma once

#include "Transform.h"
#include "RuleInstance.h"

// ------------------------------------
// Rule
// ------------------------------------

class Rule
{
public:
	Rule(const std::string& name);
	~Rule(void);

    const std::string& GetName() const { return m_name; }

    const RuleInstance* GetRandomRuleInstance() const;
	RuleInstance* CreateInstance(float weight);

private:
	std::string m_name;
	std::vector<RuleInstance*> m_instances;

    float m_totalInstancesWeight;
};
