#pragma once

#include <iostream>
#include <raylib.h>

#include "raylib_wrapper.h"
#include "app_util.h"

/***********************************************************
* This class defines the world space of a 2D application
* It is responsible for the handling the transformation 
* from world coordinates to screen coordinates 
***********************************************************/
class WorldSpace
{
public:

  WorldSpace() {};

  WorldSpace(int width, int height) 
  : screen_width_ {width}
  , screen_height_ {height}
  {};

  ~WorldSpace() = default;

  /*--------------------------------------------------------
  | Update the world space
  --------------------------------------------------------*/
  void update() {}

  /*--------------------------------------------------------
  | Draw the world space
  --------------------------------------------------------*/
  void draw() 
  {
    ClearBackground(RAYWHITE);
  }

  /*--------------------------------------------------------
  | Screen-to-World transformation
  --------------------------------------------------------*/
  inline void 
  screen_to_world(const Vec2& s, Vec2& w) const
  { w = (s / scale_) + offset_; }

  /*--------------------------------------------------------
  | World-to-Screen transformation
  --------------------------------------------------------*/
  inline void 
  world_to_screen(const Vec2& w, Vec2& s) const
  { s = (w - offset_) * scale_; }

  /*--------------------------------------------------------
  | Setters
  --------------------------------------------------------*/
  inline void scale(float s) 
  { scale_ = s; }
  inline void offset(const Vec2& o)
  { offset_ = o; }
  inline void pan(const Vec2& p)
  { pan_ = p; }

  inline void scale_multiply(float s) 
  { scale_ *= s; }
  inline void offset_add(const Vec2& o)
  { offset_ += o; }

  /*--------------------------------------------------------
  | Getters
  --------------------------------------------------------*/
  int screen_width() const { return screen_width_; }
  int screen_height() const { return screen_height_; }
  float scale() const { return scale_; }
  const Vec2& zoom() const { return zoom_; }
  const Vec2& pan() const { return pan_; }


private:

  /*--------------------------------------------------------
  | Class attributes
  --------------------------------------------------------*/
  Vec2  offset_       { 0.0f, 0.0f };
  float scale_        { 1.0f };
  Vec2  zoom_         { 1.01f, 0.99f };
  Vec2  pan_          { 0.0f, 0.0f };

  int screen_width_  { 0 };
  int screen_height_ { 0 };

}; 


