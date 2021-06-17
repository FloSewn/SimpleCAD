#pragma once

#include <list>

#include "Simplex.h"
#include "raylib_wrapper.h"
#include "app_util.h"

/***********************************************************
* This class represents a two-dimensional vertex
***********************************************************/
class Vertex : public Simplex
{
public:
  Vertex() 
  : Simplex(), xy_{0.0,0.0} {}
  Vertex(float xs, float ys) 
  : Simplex(), xy_{xs,ys} {}
  Vertex(const Vec2& p) 
  : Simplex(), xy_{p} {}

  ~Vertex() = default;
  
  /*--------------------------------------------------------
  | Getters
  --------------------------------------------------------*/
  const Vec2& xy() const override { return xy_; }

  /*--------------------------------------------------------
  | Setters
  --------------------------------------------------------*/
  void xy(const Vec2& xy) { xy_ = xy; }

  /*--------------------------------------------------------
  | Ostream of vertex
  --------------------------------------------------------*/
  std::ostream& print(std::ostream& os) const override
  {
    return os << "V: " << xy();
  }

  /*--------------------------------------------------------
  | Reset routine
  --------------------------------------------------------*/
  void reset() override { Simplex::reset(); }

  /*--------------------------------------------------------
  | Update routine
  --------------------------------------------------------*/
  void update() override { Simplex::update(); }

  /*--------------------------------------------------------
  | Draw routine
  --------------------------------------------------------*/
  void draw(const WorldSpace& ws) const override
  {
    Vec2 xy_s;
    ws.world_to_screen( xy_, xy_s );

    if ( active_ )
      DrawCircleV( xy_s.v, 7, BLACK );
    else
      DrawCircleV( xy_s.v, 5, BLACK );

  }

private: 
  Vec2 xy_;

}; // Vertex
