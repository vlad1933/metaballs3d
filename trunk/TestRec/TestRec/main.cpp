
#include "Common.h"

#include "RuleManager.h"
#include "SceneManager.h"

int main()
{
	RuleManager ruleManager;
    RuleInstance* instance;

    Rule* start = ruleManager.CreateRule("Start");
    Rule* forward = ruleManager.CreateRule("Forward");
    Rule* turn = ruleManager.CreateRule("Turn");

    instance = start->CreateInstance(1);
    instance->AddChild(ruleManager.GetRuleByName("Forward"), Transform(0));
	
    instance = forward->CreateInstance(2);
    instance->AddChild(ruleManager.GetRuleByName("Forward"), Transform(1));

    instance = forward->CreateInstance(1);
    instance->AddChild(ruleManager.GetRuleByName("Turn"), Transform(0.1f));

    instance = turn->CreateInstance(1);
    instance->AddChild(ruleManager.GetRuleByName("Forward"), Transform(0));
    
    SceneManager sceneManager;
    sceneManager.Begin(start);
    sceneManager.Update();
    sceneManager.Update();
    sceneManager.Update();
    sceneManager.Update();
    sceneManager.Update();
    sceneManager.Update();
    sceneManager.Update();
    sceneManager.Update();

	return 0;
}