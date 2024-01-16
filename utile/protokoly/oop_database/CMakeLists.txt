cmake_minimum_required(VERSION 3.27)
project(oop_database)

set(CMAKE_CXX_STANDARD 23)

add_executable(oop_database
        main.cpp
        Film.cpp
        Film.h
        Films.cpp
        Films.h
        Command.h
        Command.cpp
)
