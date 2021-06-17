#pragma once

#include <iostream>
#include <raylib.h>

#include "app_util.h"
#include "raylib_wrapper.h"
 
/***********************************************************
* Interaction between WorldSpace and MouseMarker
* -> Handles panning and zooming
***********************************************************/
void interaction(WorldSpace& world, MouseMarker& mouse);

/***********************************************************
* Interaction between BackgroundGrid and MouseMarker
* -> Handles snapping of mouse to grid nodes
***********************************************************/
void interaction(const WorldSpace&     world, 
                 const BackgroundGrid& grid,
                 MouseMarker&          mouse);

/***********************************************************
* Interaction between MouseMarker and Vertices
* -> Handles movement of vertices through mouse
***********************************************************/
void interaction(const WorldSpace&     world, 
                 SimplexContainer&     objects,
                 MouseMarker&          mouse);
