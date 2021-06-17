#include <iostream>
#include <raylib.h>

#include "app_util.h"
#include "raylib_wrapper.h"
#include "interactions.h"

#include "MouseMarker.h"
#include "WorldSpace.h"
#include "BackgroundGrid.h"
#include "SimplexContainer.h"
#include "Vertex.h"
#include "Edge.h"

/***********************************************************
* Interaction between WorldSpace and MouseMarker
* -> Handles panning and zooming
***********************************************************/
void interaction(WorldSpace& world, MouseMarker& mouse)
{ 
  Vec2 mpos_s  = mouse.screen_position();
  Vec2 mpos_w1 = mpos_s / world.scale();

  const Vec2 zoom = world.zoom();

  // Handle zooming
  if ( IsKeyDown( KEY_Q ) ) 
    world.scale_multiply( zoom.x );
  if ( IsKeyDown( KEY_A ) ) 
    world.scale_multiply( zoom.y );

  Vec2 mpos_w2 = mpos_s / world.scale();
  world.offset_add( mpos_w1 - mpos_w2 );

  // Handle panning
  if ( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) )
    world.pan( mpos_w1 );

  if ( IsMouseButtonDown( MOUSE_BUTTON_LEFT ) )
  {
    const Vec2 pan_start = world.pan();
    Vec2 dxy = pan_start - mpos_w1;
    world.offset_add( dxy );
    world.pan( mpos_w1 );
  }

} /* interaction(WorldSpace, MouseMarker) */


/***********************************************************
* Interaction between BackgroundGrid and MouseMarker
* -> Handles snapping of mouse to grid nodes
***********************************************************/
void interaction(const WorldSpace&     world, 
                 const BackgroundGrid& grid,
                 MouseMarker&          mouse)
{
  Vec2 marker_pos = GetMousePosition();
  world.screen_to_world( marker_pos, marker_pos ); 

  const Vec2 delta = grid.delta();

  int i = (marker_pos.x + 0.5 * delta.x) / delta.x;
  int j = (marker_pos.y + 0.5 * delta.y) / delta.y;

  marker_pos.x = i * delta.x;
  marker_pos.y = j * delta.y;

  // Clip to grid minima & maxima
  const Vec2 lower = grid.lower_bound();
  const Vec2 upper = grid.upper_bound();

  marker_pos.x = std::max( marker_pos.x, lower.x );
  marker_pos.x = std::min( marker_pos.x, upper.x );

  marker_pos.y = std::max( marker_pos.y, lower.y );
  marker_pos.y = std::min( marker_pos.y, upper.y );

  world.world_to_screen( marker_pos, marker_pos );

  mouse.marker_position( marker_pos );

} /* interaction(WorldSpace, BackgroundGrid, MouseMarker) */

/***********************************************************
* Interaction between MouseMarker and Vertices
* -> Handles movement of vertices through mouse
***********************************************************/
void interaction(const WorldSpace&     world, 
                 SimplexContainer&     objects,
                 MouseMarker&          mouse)
{
  Vec2 marker_world {};
  world.screen_to_world( mouse.marker_position(), 
                         marker_world );

  // No active object -> Find nearest object
  //--------------------------------------------------------
  if (!mouse.simplex() )
  {
    Simplex* snap = nullptr;

    // Check if mouse is over any object
    for (const auto& s_ptr : objects)
    {
      Vec2 diff = s_ptr->xy() - marker_world;
      Simplex* ptr = s_ptr.get();

      if (  diff.near_zero_values(0.005) 
         && typeid(*ptr) == typeid(Vertex))
      {
        snap = ptr;
        break;
      }
    }

    // Object has been detected
    if (snap)
    { 
      mouse.hover( snap );

      if ( IsMouseButtonDown( MOUSE_BUTTON_RIGHT) )
      {
        mouse.simplex( snap );
        snap->active( true );
      }
    }
  }


  // Active object exists -> Move object
  //--------------------------------------------------------
  Simplex* mouse_simplex = mouse.simplex();

  if ( mouse_simplex )
  {
    // Move object
    if ( IsMouseButtonDown(MOUSE_BUTTON_RIGHT) )
    {
      if ( typeid(*mouse_simplex) == typeid(Vertex) )
      {
        Vertex* v = reinterpret_cast<Vertex*>(mouse_simplex);
        v->xy( marker_world );
        v->updating( true );
      }
    }

    // Release object
    if ( IsMouseButtonReleased( MOUSE_BUTTON_RIGHT ) )
    {
      mouse_simplex->active( false );
      mouse.simplex( nullptr );
    }

  }


} /* interaction(WorldSpace, SimplexContainer, MouseMarker) */
