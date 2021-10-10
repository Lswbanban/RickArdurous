Rick Ardurous

# What is it

Rick Ardurous is an attempt to clone the famous old Rick Dangerous on the Arduboy platform.

# Bug list

# To do
- Editor
	- limit the vertical puzzle screen to 4
	- MapManager::MAX_UPDATABLE_ITEM_COUNT can be computed by the Editor and saved in MapDataConstVariables
	- add undo/redo feature
- Game Engine Optim
	- the mirror of the left wall is not correct for the coordinate x=0 (example in the main menu level)
	- add the PSTR()/F() macro around the menu strings?
	- bug in Rick state machine, from Fall to Death (for example jump in dynamite explosion)
- Sound/LED FX
	- different sound for picking crate/statuette/graal
	- dynamite explosion

# New items to come
- And I don't want to do the trigger + moving platform. But we can have trigger plate + door or trigger plate + boulder.
- And I don't like the bat, so I don't want it (fire do not kill it, but make it move, this is not logical)?

