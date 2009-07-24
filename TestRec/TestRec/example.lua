----------------------------------------------------------------------
-- A basic ruleset
----------------------------------------------------------------------

-- Start 

Start = Rule("Start")
Start:Child("Init")

-- Init

Init = Rule("Init")
-- TODO: init scale and color
Init:Child("Forward")

-- Move forward 

Forward = Rule("Forward")
-- TODO: translation
Forward:Child("Forward") -- continue forward

-- Turn 90°

Turn = Rule("Forward", 0.1)
Turn:Child("Forward") -- continue forward
-- TODO: set rotation
Turn:Child("Forward") -- start a new branch

