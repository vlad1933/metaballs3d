#include "RuleManager.h"

// ------------------------------------
// RuleManager
// ------------------------------------

RuleManager::RuleManager()
{
    m_lua.RegisterFunction("__createRule", &RuleManager::Lua_CreateRule);
    m_lua.RegisterFunction("__addRule", &RuleManager::Lua_AddRule);
    m_lua.WriteGlobal("__rule_manager", this);

    m_lua.DoFile("rules.lua");
}

RuleManager::~RuleManager()
{
}

Rule* RuleManager::CreateRule(const std::string& name)
{
    Rule* rule = GetRuleByName(name);
    if(!rule)
    {
        rule = new Rule(name);
        m_rules.push_back(rule);
    }
    return rule;
}

Rule* RuleManager::GetRuleByName(const std::string& name)
{
    for(size_t i=0; i<m_rules.size();i++)
    {
        if(m_rules[i]->GetName() == name)
        {
            return m_rules[i];
        }
    }
    return NULL;
}

void RuleManager::ReadFile(const std::string& path)
{
    m_lua.DoFile(path);
}

int RuleManager::Lua_CreateRule(lua_State* state)
{
    LuaManager* luaManager = LuaManager::GetFromState(state);

    float weight = 0;
    std::string ruleName;
    RuleManager* ruleManager = NULL;

    luaManager->PopValue(&weight);
    luaManager->PopValue(&ruleName);
    luaManager->ReadGlobal("__rule_manager", &ruleManager);

    Rule* rule = ruleManager->CreateRule(ruleName);
    RuleInstance* instance = rule->CreateInstance(weight);

    luaManager->PushValue(instance);

    return 1;
}

int RuleManager::Lua_AddRule(lua_State* state)
{
    LuaManager* luaManager = LuaManager::GetFromState(state);

    std::string ruleName;
    RuleInstance* instance = NULL;
    RuleManager* ruleManager = NULL;

    luaManager->PopValue(&instance);
    luaManager->PopValue(&ruleName);
    luaManager->ReadGlobal("__rule_manager", &ruleManager);  

    instance->AddChild(ruleManager->CreateRule(ruleName), Transform());
    return 0;
}
