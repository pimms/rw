cmake_minimum_required(VERSION 2.8)
project(GAME)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

file(GLOB_RECURSE SRCS src/*.cpp)
file(GLOB_RECURSE HDRS src/*.h)
add_executable(rwater ${SRCS} ${HDRS})



set(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BOX2D_INSTALL OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_UNITTESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/liquidfun/liquidfun/Box2D/)
target_include_directories(Box2D PUBLIC "thirdparty/liquidfun/liquidfun/Box2D")
target_include_directories(rwater PUBLIC "thirdparty/liquidfun/liquidfun/Box2D")
set_target_properties(Box2D PROPERTIES OUTPUT_NAME Box2D)

add_dependencies(rwater Box2D)
