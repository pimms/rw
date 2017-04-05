cmake_minimum_required(VERSION 2.8)
project(GAME)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

file(GLOB_RECURSE SRCS src/*.cpp)
file(GLOB_RECURSE HDRS src/*.h)
add_executable(rwater ${SRCS} ${HDRS})


# This is the worst possible way to include Box2D, but I really can't be bothered
# cleaning this up right now.
set(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BOX2D_INSTALL OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_UNITTESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/liquidfun/liquidfun/Box2D/)
target_include_directories(Box2D PUBLIC "thirdparty/liquidfun/liquidfun/Box2D")
set_target_properties(Box2D PROPERTIES OUTPUT_NAME Box2D)

target_include_directories(rwater PUBLIC "thirdparty/liquidfun/liquidfun/Box2D")
add_dependencies(rwater Box2D)

# +-------------------+
# | Findable packages |
# +-------------------+

# MacOS/MacPorts voodoo
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /opt/local/lib)
set(CMAKE_FIND_FRAMEWORK NEVER)

# SFML - link 'em all
find_package(SFML 2.4 COMPONENTS system window graphics network audio REQUIRED)
message("SFML libs: " ${SFML_LIBRARIES})
target_link_libraries(rwater ${SFML_LIBRARIES})
target_include_directories(rwater PUBLIC ${SFML_INCLUDE_DIR})
