#pragma once

#include "Common.h"

#include "Rule.h"
#include "LuaManager.h"

// ------------------------------------
// RuleManager
// ------------------------------------

class RuleManager
{
public:
	RuleManager();
	~RuleManager();

	Rule* CreateRule(const std::string& name);
	Rule* GetRuleByName(const std::string& name);

    void ReadFile(const std::string& path);

public:
    static int Lua_CreateRule(lua_State* state);
    static int Lua_AddRule(lua_State* state);

private:
	std::vector<Rule*> m_rules;
    LuaManager m_lua;
};
