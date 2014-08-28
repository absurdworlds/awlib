hrengin TODO list
=================

## core

+ Implement virtual filesystem: all file access will be performed through emulated virtual filesystem. Virtual file paths will be translated into physical paths to files in archives and data on disk.
+ Implement hrengin archive format.
+ Implement hrengin model format.
+ Implement hrengin map/scene format.
+ Create hrengin shell, for ingame testing & debugging tasks

## graphics

+ Create GUI manager (ongoing)
+ Rewrite video manager into separate smaller classes (ongoing)
+ Create GUI for hrengin shell
+ Write interface for rendering vertex primitives

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

## tools

+ Create hrengin model editor
