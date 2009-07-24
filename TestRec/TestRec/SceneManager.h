#pragma once

#include "Common.h"
#include "Node.h"

// ------------------------------------
// SceneManager
// ------------------------------------

class SceneManager
{
public:
	SceneManager(void);
	~SceneManager(void);

    void Begin(Rule* start);
    void Update();

private:
    std::vector<Node*> m_currentNodes;
    std::vector<Node*> m_pastNodes;
};
