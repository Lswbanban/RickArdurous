Rick Ardurous

# What is it

Rick Ardurous is an attempt to clone the famous old Rick Dangerous on the Arduboy platform.

# Bug list
- Bug: check why the bullet is not killed when hitting a enemy
- Potential bug: an Enemy can kill another one if they cross each other: is it ok with level design?
- Bug: during the death anim, Rick (and probably also Enemy can go outside the level, letting the camera to draw the memory)

# To do

## Enemy
- The death state for both type of Enemy (Mummy and Skeleton)
- Implement the logic for the Skeleton to wait and follow Rick

# New items to come
- The destroyable blocks (with the dynamite to create a path)
- The destroyable stalagmites that block the way (destroyable with the dynamite)
- A falling item, like a stalagtite (similar to the falling grill in the original game)
- The rolling boulder
- A scorpion as a new type of Enemy (this cannot be killed by the bullet, because too short). But need to define the AI logic, to see if it is interesting.
- And I don't want to do the trigger + moving platform. But we can have trigger plate + door or trigger plate + boulder.
- And I don't like the bat, so I don't want it (fire do not kill it, but make it move, this is not logical)?

