cmake_minimum_required(VERSION 3.22)
project(SFML_Snake)

set(CMAKE_CXX_STANDARD 14)

include_directories(headers /usr/include C:/SFML-2.0/include)
link_directories("C:/SFML-2.0")

add_executable(SFML_Snake
        functions.cpp
        functions.h
        main.cpp)
