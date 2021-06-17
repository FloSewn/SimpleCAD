#pragma once

#include <iostream>
#include <raylib.h>

#include "app_util.h"
#include "raylib_wrapper.h"


/***********************************************************
* This class defines a background grid, to which 
* edges the mouse snaps
***********************************************************/
class BackgroundGrid
{
public:
  BackgroundGrid() {}
  BackgroundGrid(const Vec2& xy1, const Vec2& xy2, 
                 int nx, int ny) 
  : xy1_{xy1}
  , xy2_{xy2}
  , nx_{nx}
  , ny_{ny} 
  {
    dxy_.x = (xy2_.x-xy1_.x) / (float) nx;
    dxy_.y = (xy2_.y-xy1_.y) / (float) ny;
  }

  ~BackgroundGrid() = default;


  /*--------------------------------------------------------
  | Update the background grid
  --------------------------------------------------------*/
  void update() {}


  /*--------------------------------------------------------
  | Main drawing routine for the background grid
  --------------------------------------------------------*/
  void draw(const WorldSpace& bg) const
  {
    draw_grid(bg);
  }

  /*--------------------------------------------------------
  | Getters
  --------------------------------------------------------*/
  const Vec2& lower_bound() const { return xy1_; }
  const Vec2& upper_bound() const { return xy2_; }
  const Vec2& delta() const { return dxy_; }


private:

  /*--------------------------------------------------------
  | Draw the actual grid
  --------------------------------------------------------*/
  void draw_grid(const WorldSpace& bg) const;

  /*--------------------------------------------------------
  | Class attribues 
  --------------------------------------------------------*/
  int nx_ { 0 };
  int ny_ { 0 };

  // Bounding box 
  Vec2 xy1_ { 0.0f, 0.0f};
  Vec2 xy2_ { 0.0f, 0.0f};
  Vec2 dxy_ { 0.0f, 0.0f};


};
