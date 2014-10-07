hrengin
=======

## What is this?  ##

hrengin (formerly hrEngine) is a general purpose game engine.

hrengin is based on modular architecture, that is, hrengin consists of several dynamically linked modules, which are intended to be easily replaceable (ideally without recompiling other modules).

Please note that hrengin is only a library and not a standalone game engine.

### Status ###

hrengin currently is in its early development, and contains a lot of unfinished and temporary code, and completely lacks documentation. 
Even so, it is still possible to use it for developing a game, provided one will write own game logic.

## Dependencies ##

* Bullet physics
* Irrlicht
* OpenAL Soft
* RakNet

However, it is possible to replace any of those with another library, provided you write your own wrapper.

## Compiling ##

See BUILD. Wish you luck!

### Configuration ###

## Modules ##

hrengin consists of following modules:
+ game
+ core
+ graphics
+ physics
+ audio
+ platform
