hrengin TODO list
=================

## core

+ [ ] Implement virtual filesystem: all file access will be performed through emulated virtual filesystem. Virtual file paths will be translated into physical paths to files in archives and data on disk.
+ [ ] Implement hrengin archive format.
+ [ ] Implement hrengin model format.
+ [ ] Implement hrengin map/scene format.
+ [ ] Rewrite hrengin shell (add more elegant way to define console commands)
+ [ ] Update config manager to parse any settings, not only hardcoded ones
+ [ ] Update HDF parser, add possibility to read values as hdf::Value class, instead of predefined type

## graphics

+ [ ] ~~Add hook for debug drawers~~
+ [ ] Implement IRenderable
    * IVisNode will be created using ISceneManager::createVisNode(IRenderable *)
    * VisNode will actually hook the renderable to underlying engine
+ [ ] Write interface for rendering vertex primitives
+ [ ] IInputManager: revert receiver list from std::forward_list to std::vector
+ [ ] IInputManager: split into subclasses
+ [ ] Finish OGRE wrapper
    * [ ] Model, texture loading
    * [ ] Scene rendering
    * [ ] GUI
+ [ ] Re-add OSG wrapper

## gui

+ [ ] Write own gui system instead of Irrlicht's
+ [ ] Key binding manager, takes an keyboard input event and translates keystrokes into bindings

## physics

+ [ ] Improve kinematic body support

## audio

+ [ ] Figure out resource management

## game

+ [ ] Write navmesh/waypoint navigation system
+ [ ] Improve parenting
+ [ ] Rewrite event manager to use fixed time steps
+ [ ] Add event manager (a different one, for handling game events)

## tools

+ [ ] Create hrengin model editor

## other

+ [ ] Test custom allocator for units: spawn 10000 units w/o visual model, moving in circles, and measure time taken for event manager to process all of them with and without custom continuous allocator
+ [ ] Write doxygen documentation
+ [x] Write GNU makefiles
+ [ ] Write premake scripts to replace VC projects
+ [x] Tackle with -fvisibility=hidden and visibility attributes