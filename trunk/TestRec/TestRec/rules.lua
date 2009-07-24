----------------------------------------------------------------------
-- Basic functions
----------------------------------------------------------------------

function _newRule(name, cppInstance)
	rule = {}
	
	rule.cppInstance = cppInstance
	
	rule.translation = {0,0,0}
	rule.scale = 1	
	
	function rule:Translation(x,y,z)
		self.translation = {x,y,z}
	end
	
	function rule:Child(name)
		__addRule(__rule_manager, name, cppInstance)
	end
	
	return rule
end

function Rule(name, weight)
	if weight == nil then 
		weight = 1
	end
	cppInstance = __createRule(__rule_manager, name, weight)
	return _newRule(name, cppInstance)
end