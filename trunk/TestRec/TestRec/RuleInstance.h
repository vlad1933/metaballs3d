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
	RuleInstance(void); 
	~RuleInstance(void);

	void AddChild(Rule* rule, Transform transform);

private:
	std::vector<Child> m_childs; 
	float m_absoluteProbability;
};
