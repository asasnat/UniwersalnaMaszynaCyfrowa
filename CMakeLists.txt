cmake_minimum_required(VERSION 3.14.0)
project(CodeJam2024_asasnat VERSION 0.1.0 LANGUAGES C CXX)

if(DEFINED ARC_WEB_BUILD)
set(CUSTOM_ARGS "--use-port=sdl2 --use-port=sdl2_image:formats=png --use-port=sdl2_ttf --preload-file res")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_ARGS}")
set(CMAKE_EXECUTABLE_SUFFIX ".html") # adds a whole bunch of sh... that I don't want or need
else()
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
endif()

include_directories("include")

add_executable(CodeJam2024_asasnat src/main.cpp src/window.cpp src/entity.cpp src/player.cpp src/computer.cpp src/room.cpp src/ui.cpp # root dir
               src/puzzles/puzzle.cpp src/puzzles/wires.cpp) # puzzles
#add_executable(CodeJam2024_asasnat src/test.cpp)

if(NOT DEFINED ARC_WEB_BUILD)
target_link_libraries(CodeJam2024_asasnat SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
endif()
