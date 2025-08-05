cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Enigma)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(Enigma main.cpp
        Header/gui_window.h
        Header/ShortestPath.h
        Source/gui_window.cpp
        Source/ShortestPath.cpp)
target_link_libraries(Enigma sfml-system sfml-window sfml-graphics sfml-audio)
