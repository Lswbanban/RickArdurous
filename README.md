Rick Ardurous

# What is it

Rick Ardurous is an attempt to clone the famous old Rick Dangerous on the Arduboy platform.

# Bug list

# To do
- Editor
	- MapManager::MAX_UPDATABLE_ITEM_COUNT can be computed by the Editor and saved in MapDataConstVariables
	- add undo/redo feature
	- Stalagmite instance are duplicated in puzzle screen zero when it is the end of the game
- Game Engine Optim
	- add the PSTR()/F() macro around the menu strings?
	- bug in Rick state machine, from Fall to Death (for example jump in dynamite explosion)
	- the mirror of the left wall is not correct for the coordinate x=0 (example in the main menu level)
	- bug in the checkpoint for puzzle screen 9
- Sound/LED FX
	- different sound for picking crate/statuette/graal
	- dynamite explosion

# New items to come
- And I don't want to do the trigger + moving platform. But we can have trigger plate + door or trigger plate + boulder.
- And I don't like the bat, so I don't want it (fire do not kill it, but make it move, this is not logical)?

