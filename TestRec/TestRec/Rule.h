#pragma once

#include "Transform.h"
#include "RuleInstance.h"

// ------------------------------------
// Rule
// ------------------------------------

class Rule
{
public:
	Rule(void);
	~Rule(void);

	void AddInstance(Transform tansform, float probability);

private:
	std::string m_name;
	std::vector<RuleInstance> m_instances;
};
