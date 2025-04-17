cmake_minimum_required(VERSION 3.10)
project(RoadConnections LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/renderer.cpp
  src/event_handler.cpp
  src/texture_manager.cpp
  src/game_controller.cpp
  src/utils/game_parser.cpp
  src/utils/texture.cpp
  src/object/city.cpp
  src/object/camera.cpp
  src/object/road.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
  include
  include/utils
  include/object
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
)

# Debug configuration
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:
    -g
    -O0
    -Wall
    -Wextra
    -Wpedantic
    -fstandalone-debug
  >
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:_DEBUG>
)

# Release configuration
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Release>:
    -O3
    -DNDEBUG
  >
)

# Fix linker flags (changed from target_link_options to target_compile_definitions)
target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Release>:_RELEASE>
)