#pragma once
#include <raylib.h>

#include "raylib_wrapper.h"
#include "WorldSpace.h"
#include "Facet.h"

/***********************************************************
* A simple triangle
***********************************************************/
class Triangle : public Facet
{
public:

  Triangle() {}

  Triangle(const Vertex* v1, 
           const Vertex* v2, 
           const Vertex* v3) 
    : v1_ {v1}
    , v2_ {v2}
    , v3_ {v3}
  { (v1_->xy() + v2_->xy() + v3_->xy()) / 3.0; }

  ~Triangle() = default;

  /*--------------------------------------------------------
  | Getters
  --------------------------------------------------------*/
  const Vec2& xy() const override { return xy_; }

  /*--------------------------------------------------------
  | Ostream of triangle
  --------------------------------------------------------*/
  std::ostream& print(std::ostream& os) const override
  {
    return os << *v1_ << " -> " << *v2_ << " -> " << *v3_;
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
    if (v1_->updating() || v2_->updating() || v3_->updating())
      updating_ = true;

    if ( updating_ == false ) 
      return;

    xy_ = (v1_->xy() + v2_->xy() + v3_->xy()) / 3.0;
  }

  /*--------------------------------------------------------
  | Draw the triangle on the screen
  --------------------------------------------------------*/
  void draw(const WorldSpace& ws) const
  {
    Vec2 v1_s, v2_s, v3_s;
    ws.world_to_screen( v1_->xy() , v1_s );
    ws.world_to_screen( v2_->xy() , v2_s );
    ws.world_to_screen( v3_->xy() , v3_s );

    DrawLineEx(v1_s.v, v2_s.v, 2.0, BLACK);
    DrawLineEx(v2_s.v, v3_s.v, 2.0, BLACK);
    DrawLineEx(v3_s.v, v1_s.v, 2.0, BLACK);
  }


private:

  const Vertex* v1_;
  const Vertex* v2_;
  const Vertex* v3_;

  Vec2 xy_ { 0.0f, 0.0f };

}; // Triangle
