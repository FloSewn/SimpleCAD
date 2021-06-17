#include <iostream>
#include <raylib.h>

#include "raylib_wrapper.h"
#include "WorldSpace.h"
#include "BackgroundGrid.h"


/***********************************************************
* 
***********************************************************/
void BackgroundGrid::draw_grid(const WorldSpace& bg) const
{
  float fwidth  = (float)bg.screen_width();
  float fheight = (float)bg.screen_height();

  Vec2 top_left_w, bottom_right_w;
  bg.screen_to_world( {0.0f, 0.0f}, top_left_w );
  bg.screen_to_world( {fwidth, fheight}, bottom_right_w );


  for ( float y = xy1_.y; y <= xy2_.y; y += dxy_.y )
  {
    if (y < top_left_w.y || y > bottom_right_w.y)
      continue;

    Vec2 start_w { xy1_.x, y };
    Vec2 end_w   { xy2_.x, y };

    Vec2 start_s, end_s;
    bg.world_to_screen( start_w, start_s );
    bg.world_to_screen( end_w, end_s );

    DrawLineEx( start_s.v, end_s.v, 1.0, BLACK );
  }

  for ( float x = xy1_.x; x <= xy2_.x; x += dxy_.x )
  {
    if (x < top_left_w.x || x > bottom_right_w.x)
      continue;

    Vec2 start_w { x, xy1_.y };
    Vec2 end_w   { x, xy2_.y };

    Vec2 start_s, end_s;
    bg.world_to_screen( start_w, start_s );
    bg.world_to_screen( end_w, end_s );

    DrawLineEx( start_s.v, end_s.v, 1.0, BLACK );
  }

}

