#pragma once

#include "Common.h"

#include "Transform.h"

// ------------------------------------
// Forward Declarations
// ------------------------------------

class Rule;

// ------------------------------------
// RuleInstance
// ------------------------------------

typedef std::pair<Rule*, Transform> Child;

class RuleInstance
{
public:
	RuleInstance(Rule* rule, float weight); 
	~RuleInstance(void);

    float GetWeight() const { return m_weight; }
    const std::vector<Child>& GetChilds() const { return m_childs; }

	void AddChild(Rule* rule, Transform transform);

private:
    Rule* m_rule;
	std::vector<Child> m_childs; 
	float m_weight;
};
