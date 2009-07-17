#pragma once

#include "Common.h"

#include "NodeState.h"
#include "Rule.h"

// ------------------------------------
// Node
// ------------------------------------

class Node
{
public:
	Node(Rule* rule, const NodeState& state);
	~Node(void);

    const Rule* GetRule() const {return m_rule;}
    const NodeState& Getstate() const {return m_state;}

private:
	Rule* m_rule;
	NodeState m_state;
};
