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
	Node(void);
	~Node(void);

private:
	Rule* m_rule;
	NodeState m_state;
};
