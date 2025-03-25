cmake_minimum_required(VERSION 3.10)
project(RoadConnections LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME}
  src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
  include
  ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
  ${SDL2_LIBRARIES}
)

# Debug configuration
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:
    -g
    -O0
    -Wall
    -Wextra
    -Wpedantic
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