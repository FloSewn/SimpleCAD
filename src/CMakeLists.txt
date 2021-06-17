set( APP SimpleCAD )

add_executable(${APP}
               BackgroundGrid.cpp
               interactions.cpp
               main.cpp
)

target_include_directories( ${APP} PRIVATE ${RAYLIB_PATH} )

target_link_libraries( ${APP}
  PRIVATE raylib
  PRIVATE m
  INTERFACE GL
  INTERFACE pthread
  INTERFACE dl
  INTERFACE rt
  INTERFACE X11
)

install( TARGETS ${APP} RUNTIME DESTINATION ${BIN} )
