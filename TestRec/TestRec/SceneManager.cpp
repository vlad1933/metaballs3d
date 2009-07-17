#include "SceneManager.h"

// ------------------------------------
// SceneManager
// ------------------------------------

SceneManager::SceneManager(void)
{
}

SceneManager::~SceneManager(void)
{
}

void SceneManager::Begin(Rule* start)
{
    Node* node = new Node(start, NodeState());
    m_currentNodes.push_back(node);
}

void SceneManager::Update()
{
    //Create a temporary copy of the vector, maybe use double buffering if necessary
    std::vector<Node*> temp = m_currentNodes;
    m_currentNodes.clear();
    
    for (size_t i=0; i<temp.size(); i++)
    {
        //For each open nodes
        Node* node = temp[i];

        //Choose a random rule variation to apply
        const RuleInstance* instance = node->GetRule()->GetRandomRuleInstance();
        const std::vector<Child> nextRules = instance->GetChilds();
        for (size_t j=0; j<nextRules.size(); j++)
        {
            //For each rule to call
            Child next = nextRules[j];
            //Open a new node
            Node* newNode = new Node(next.first, next.second.Apply(node->Getstate()));
            //And push it in the open nodes list
            m_currentNodes.push_back(newNode);
        } 

        //Push the node to closed nodes list
        m_pastNodes.push_back(node);
    }
}