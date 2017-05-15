cmake_minimum_required(VERSION 2.8)
project(GAME)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

find_package(Threads)
# Rogue Waters source files
file(GLOB_RECURSE RWSRCS src/*.cpp)
file(GLOB_RECURSE RWHDRS src/*.h)
add_executable(rwater ${RWSRCS} ${RWHDRS})
target_compile_features(rwater PRIVATE cxx_range_for)
target_link_libraries(rwater ${CMAKE_THREAD_LIBS_INIT})

# Unit Testing source files (all rw-sources, bar main.cpp)
list(REMOVE_ITEM RWSRCS ${CMAKE_SOURCE_DIR}/src/main.cpp)
file(GLOB_RECURSE TESTSRCS test/*.cpp)
file(GLOB_RECURSE TESTHDRS test/*.h)
add_executable(tests ${RWSRCS} ${RWHDRS} ${TESTSRCS} ${TESTHDRS})
target_include_directories(tests PRIVATE "${CMAKE_SOURCE_DIR}/src")
target_compile_features(tests PRIVATE cxx_range_for)

# This is the worst possible way to include Box2D, but I really can't be bothered
# cleaning this up right now.
set(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BOX2D_INSTALL OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_UNITTESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/liquidfun/liquidfun/Box2D/)
target_include_directories(Box2D PUBLIC "thirdparty/liquidfun/liquidfun/Box2D")
set_target_properties(Box2D PROPERTIES OUTPUT_NAME Box2D)
target_include_directories(rwater PUBLIC "thirdparty/liquidfun/liquidfun/Box2D")
target_include_directories(tests PUBLIC "thirdparty/liquidfun/liquidfun/Box2D")
add_dependencies(rwater Box2D)
add_dependencies(tests Box2D)

# Google Test
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/googletest/)
add_dependencies(tests gtest)
target_link_libraries(tests gtest)
target_include_directories(tests PUBLIC "thirdparty/googletest/googletest/include/")

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
target_link_libraries(tests ${SFML_LIBRARIES})
target_include_directories(rwater PUBLIC ${SFML_INCLUDE_DIR})
target_include_directories(tests PUBLIC ${SFML_INCLUDE_DIR})
