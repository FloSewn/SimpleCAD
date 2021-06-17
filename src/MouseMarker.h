#pragma once

#include <iostream>
#include <raylib.h>

#include "raylib_wrapper.h"
#include "app_util.h"
#include "Simplex.h"


/***********************************************************
* This class defines a mouse marker for the user
* and handles the access to the mouse position
***********************************************************/
class MouseMarker
{
public:

  MouseMarker() 
  : screen_pos_ { GetMousePosition() }
  {};
  ~MouseMarker() = default;
   
  /*--------------------------------------------------------
  | Reset the mouse marker
  --------------------------------------------------------*/
  void reset() { hover_ = nullptr; }

  /*--------------------------------------------------------
  | Update the mouse marker
  --------------------------------------------------------*/
  void update() 
  { 
    screen_pos_ = GetMousePosition(); 
    
    // Keep current simplex marked as active
    if ( simplex_ ) simplex_->active( true );
  }

  /*--------------------------------------------------------
  | Draw the mouse marker
  --------------------------------------------------------*/
  void draw( const BackgroundGrid& grid ) 
  {
    if ( hover_ || simplex_ )
      DrawCircleLines(marker_pos_.v.x, marker_pos_.v.y, 
                      10, BLACK);
    else
      DrawCircleV(marker_pos_.v, 5, RED);
  }

  /*--------------------------------------------------------
  | Getters
  --------------------------------------------------------*/
  const Vec2& screen_position() const { return screen_pos_; }
  const Vec2& marker_position() const { return marker_pos_; }
  Simplex* simplex() { return simplex_; }
  Simplex* hover() { return hover_; }

  /*--------------------------------------------------------
  | Setters
  --------------------------------------------------------*/
  void screen_position(const Vec2& p) { screen_pos_ = p; }
  void marker_position(const Vec2& p) { marker_pos_ = p; }
  void simplex( Simplex* s ) { simplex_ = s; }
  void hover( Simplex* s ) { hover_ = s; }

private:

  /*--------------------------------------------------------
  | Class attribues 
  --------------------------------------------------------*/
  // The actual mouse position on screen
  Vec2 screen_pos_ { 0.0f, 0.0f };

  // The mouse marker position to draw on screen
  Vec2 marker_pos_ { 0.0f, 0.0f };

  // A simplex that is currently grabbed by the mouse
  Simplex* simplex_ = nullptr; 

  // A simplex the mouse is currently hovering on
  Simplex* hover_ = nullptr; 

};
