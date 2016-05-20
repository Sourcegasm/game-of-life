cmake_minimum_required(VERSION 2.7)
project(Game_of_Life)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/game.cpp src/physics.cpp)
add_executable(Game_of_Life ${SOURCE_FILES})

target_link_libraries(Game_of_Life sfml-graphics)
target_link_libraries(Game_of_Life sfml-window)
target_link_libraries(Game_of_Life sfml-system)
