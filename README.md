# Rick Ardurous

## What is it?

Rick Ardurous is a game developed for the Arduboy, and inspired by the retro-game Rick Dangerous, where the player takes the role of an adventurer exploring caves in the hope of finding the Grail. The game propose a series of puzzles fitting in one screen. The player will have to reach the exit point of each screen to move to the next puzzle. The game propose 12 puzzle-screens with an increasing difficulty.

## Documentation

For more details, please read the documentation by opening the Doc/Index.html file.

## License

This project is open source, both for the game and the Editor.

## Bug list

## To do
- Editor
	- Add a stats info display on the level in the View Menu
	- MapManager::MAX_UPDATABLE_ITEM_COUNT can be computed by the Editor and saved in MapDataConstVariables
	- Fix the drawing of the sprites in the toolbar
- Game Engine Optim
	- add the PSTR()/F() macro around the menu strings?
	- bug in Rick state machine, from Fall to Death (for example jump in dynamite explosion)
- Sound/LED FX
	- different sound for picking crate/statuette/graal
	- dynamite explosion

