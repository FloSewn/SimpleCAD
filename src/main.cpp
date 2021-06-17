#include <iostream>
#include <raylib.h>

#include "WorldSpace.h"
#include "BackgroundGrid.h"
#include "MouseMarker.h"
#include "Triangle.h"
#include "Quad.h"
#include "SimplexContainer.h"
#include "Vertex.h"
#include "Edge.h"
#include "raylib_wrapper.h"
#include "interactions.h"

int main()
{
  /*--------------------------------------------------------
  | Initialization
  --------------------------------------------------------*/
  const int screen_width = 800;
  const int screen_height = 800;

  InitWindow(screen_width, screen_height, 
      "Pan and Zoom Example");

  WorldSpace world_space {screen_width, screen_height};
  world_space.scale(100.0f);

  MouseMarker mouse {};

  BackgroundGrid grid {{0.0f, 0.0f}, {10.0f,10.0f}, 10, 10};

  /*--------------------------------------------------------
  | Create some sample objects
  --------------------------------------------------------*/
  SimplexContainer objects {};

  /* Sample edge */
  Vertex* v1 = objects.add( 
      std::make_unique<Vertex>( 3.0f, 3.0f )
  );
  Vertex* v2 = objects.add( 
      std::make_unique<Vertex>( 2.0f, 2.0f )
  );
  Edge* e1 = objects.add(
      std::make_unique<Edge>( v1, v2 )
  );


  /* Sample triangle */
  Vertex* v3 = objects.add( 
      std::make_unique<Vertex>( 2.0f, 4.0f )
  );
  Vertex* v4 = objects.add( 
      std::make_unique<Vertex>( 4.0f, 6.0f )
  );
  Vertex* v5 = objects.add( 
      std::make_unique<Vertex>( 1.0f, 6.0f )
  );
  Triangle* t1 = objects.add(
      std::make_unique<Triangle>( v3, v4, v5 )
  );


  /* Sample quad */
  Vertex* v6 = objects.add( 
      std::make_unique<Vertex>( 5.0f, 4.0f )
  );
  Vertex* v7 = objects.add( 
      std::make_unique<Vertex>( 7.0f, 4.0f )
  );
  Vertex* v8 = objects.add( 
      std::make_unique<Vertex>( 7.0f, 6.0f )
  );
  Vertex* v9 = objects.add( 
      std::make_unique<Vertex>( 5.0f, 6.0f )
  );
  Quad* q1 = objects.add(
      std::make_unique<Quad>( v6, v7, v8, v9 )
  );

  /*--------------------------------------------------------
  | Set our game to run at 60 frames-per-second
  --------------------------------------------------------*/
  SetTargetFPS(60); 

  /*--------------------------------------------------------
  | Main game loop
  --------------------------------------------------------*/
  while (!WindowShouldClose())    
  {
    /*------------------------------------------------------
    | Resets
    ------------------------------------------------------*/
    mouse.reset();
    for (const auto& s_ptr : objects)
      s_ptr->reset();
    
    /*------------------------------------------------------
    | Interactions
    ------------------------------------------------------*/
    interaction( world_space, mouse );
    interaction( world_space, grid, mouse );
    interaction( world_space, objects, mouse );

    /*------------------------------------------------------
    | Update
    ------------------------------------------------------*/
    mouse.update();
    world_space.update();
    for (const auto& s_ptr : objects)
      s_ptr->update();

    /*------------------------------------------------------
    | Draw
    ------------------------------------------------------*/
    BeginDrawing();

      world_space.draw();

      grid.draw( world_space );

      for (const auto& s_ptr : objects)
        s_ptr->draw( world_space );

      mouse.draw( grid );

    EndDrawing();
  }


  /*--------------------------------------------------------
  | Close window and OpenGL context
  --------------------------------------------------------*/
  CloseWindow();

  return EXIT_SUCCESS;
}
