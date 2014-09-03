hrengin TODO list
=================

## core

+ Implement virtual filesystem: all file access will be performed through emulated virtual filesystem. Virtual file paths will be translated into physical paths to files in archives and data on disk.
+ Implement hrengin archive format.
+ Implement hrengin model format.
+ Implement hrengin map/scene format.
+ Create hrengin shell, for ingame testing & debugging tasks (current)
+ Create config manager (current)

## graphics

+ Add hook for debug drawers
+ Write interface for rendering vertex primitives
+ IInputManager: revert receiver list from std::forward_list to std::vector

## gui

+ Rewrite Irrlicht's gui system

## physics

+ Improve kinematic body support
+ Improve collision filtering support
+ Write separate raycasting class

## audio

+ Figure out resource management

## game

+ Write navmesh/waypoint navigation system
+ Improve parenting
+ Rewrite event manager to use fixed time steps
+ Add event manager (a different one, for handling game events)

## tools

+ Create hrengin model editor

## other

+ Test custom allocator for units: spawn 10000 units w/o visual model, moving in circles, and measure time taken for event manager to process all of them with and without custom continuous allocator
