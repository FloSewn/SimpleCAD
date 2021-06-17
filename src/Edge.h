#pragma once

#include <list>

#include "raylib_wrapper.h"
#include "Edge.h"
#include "Vertex.h"

/***********************************************************
* This class represents a two-dimensional vertex
***********************************************************/
class Edge : public Simplex
{
public:
  Edge(const Vertex* v1, const Vertex* v2) 
  : Simplex()
  , v1_ {v1}
  , v2_ {v2}
  { xy_ = 0.5 * (v1_->xy() + v2_->xy()); }

  ~Edge() = default;

  /*--------------------------------------------------------
  | Getters
  --------------------------------------------------------*/
  const Vec2& xy() const override { return xy_; }

  /*--------------------------------------------------------
  | Ostream of edge
  --------------------------------------------------------*/
  std::ostream& print(std::ostream& os) const override
  {
    return os << *v1_ << " -> " << *v2_;
  }

  /*--------------------------------------------------------
  | Reset routine
  --------------------------------------------------------*/
  void reset() override { Simplex::reset(); }

  /*--------------------------------------------------------
  | Update routine
  --------------------------------------------------------*/
  void update() override 
  {
    if ( v1_-> updating() || v2_->updating() )
      updating_ = true;

    if ( updating_ == false ) 
      return;

    xy_ = 0.5 * (v1_->xy() + v2_->xy());
  }

  /*--------------------------------------------------------
  | Draw routine
  --------------------------------------------------------*/
  void draw(const WorldSpace& ws) const override
  {
    Vec2 xy1_s, xy2_s;
    ws.world_to_screen( v1_->xy(), xy1_s );
    ws.world_to_screen( v2_->xy(), xy2_s );
    DrawLineEx(xy1_s.v, xy2_s.v, 2.0, BLACK );
  }

private:

  const Vertex* v1_;
  const Vertex* v2_;

  Vec2 xy_ {0.0, 0.0};

}; // Edge
