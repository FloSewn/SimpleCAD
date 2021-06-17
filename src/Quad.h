#pragma once
#include <raylib.h>

#include "raylib_wrapper.h"
#include "WorldSpace.h"
#include "Facet.h"

/***********************************************************
* A simple Quadrilateral
***********************************************************/
class Quad : public Facet
{
public:

  Quad() {}

  Quad(const Vertex* v1, const Vertex* v2, 
       const Vertex* v3, const Vertex* v4) 
    : v1_ {v1}, v2_ {v2}, v3_ {v3}, v4_ {v4}
  { 0.25 * (v1_->xy() + v2_->xy() + v3_->xy() + v4_->xy());}

  ~Quad() = default;

  /*--------------------------------------------------------
  | Getters
  --------------------------------------------------------*/
  const Vec2& xy() const override { return xy_; }

  /*--------------------------------------------------------
  | Ostream of Quad
  --------------------------------------------------------*/
  std::ostream& print(std::ostream& os) const override
  {
    return os << *v1_ << " -> " << *v2_ 
              << " -> " << *v3_ << " -> " << *v4_;
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
    if (  v1_->updating() || v2_->updating() 
       || v3_->updating() || v4_->updating() )
      updating_ = true;

    if ( updating_ == false ) 
      return;

    0.25 * (v1_->xy() + v2_->xy() + v3_->xy() + v4_->xy());
  }

  /*--------------------------------------------------------
  | Draw the Quad on the screen
  --------------------------------------------------------*/
  void draw(const WorldSpace& ws) const
  {
    Vec2 v1_s, v2_s, v3_s, v4_s;
    ws.world_to_screen( v1_->xy() , v1_s );
    ws.world_to_screen( v2_->xy() , v2_s );
    ws.world_to_screen( v3_->xy() , v3_s );
    ws.world_to_screen( v4_->xy() , v4_s );

    DrawLineEx(v1_s.v, v2_s.v, 2.0, BLACK);
    DrawLineEx(v2_s.v, v3_s.v, 2.0, BLACK);
    DrawLineEx(v3_s.v, v4_s.v, 2.0, BLACK);
    DrawLineEx(v4_s.v, v1_s.v, 2.0, BLACK);
  }


private:

  const Vertex* v1_;
  const Vertex* v2_;
  const Vertex* v3_;
  const Vertex* v4_;

  Vec2 xy_ { 0.0f, 0.0f };

}; // Quad
