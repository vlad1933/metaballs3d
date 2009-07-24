
#include "Common.h"

#include "RuleManager.h"
#include "SceneManager.h"
#include "LuaManager.h"

int main()
{
	RuleManager ruleManager;
    ruleManager.ReadFile("example.lua");
  
    SceneManager sceneManager;
    sceneManager.Begin(ruleManager.GetRuleByName("Start"));

    int iterCount = 64;
    for(int i=0; i<iterCount; i++)
    {
        sceneManager.Update();
    }

	return 0;
}