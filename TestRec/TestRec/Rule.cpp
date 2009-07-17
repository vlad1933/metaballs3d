#include "Rule.h"

#include <stdlib.h>

float random()
{
    return (float)rand()/(float)RAND_MAX;
}

Rule::Rule(const std::string& name) : m_name(name), m_totalInstancesWeight(0)
{
}

Rule::~Rule(void)
{
}

const RuleInstance* Rule::GetRandomRuleInstance() const
{
    float rand = random() * m_totalInstancesWeight;
    size_t i;
    for(i=0;rand>0 && i<m_instances.size(); i++)
    {
        rand -= m_instances[i].GetWeight();
    }
    return &m_instances[i-1];
}

RuleInstance* Rule::CreateInstance(float weight)
{
    m_totalInstancesWeight += weight;
    m_instances.push_back(RuleInstance(this, weight)); 
    return &m_instances.back();
}
