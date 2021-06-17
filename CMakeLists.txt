cmake_minimum_required(VERSION 3.5.2)
project(pan_and_zoom
        LANGUAGES CXX
        VERSION 1.0
)

set( RAYLIB_PATH /home/florian/Programs/raylib )

set( BIN ${CMAKE_SOURCE_DIR}/bin )

add_subdirectory(src)
