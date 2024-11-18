cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(jaden_delapaz_minesweeper)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/Users/jaden/Desktop/Project 3 - Minesweeper Spring 2024/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(jaden_delapaz_minesweeper main.cpp
        minesweeper.h
        minesweeper.cpp)
target_link_libraries(jaden_delapaz_minesweeper sfml-system sfml-window sfml-graphics sfml-audio)