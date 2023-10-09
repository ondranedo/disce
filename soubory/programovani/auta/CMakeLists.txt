cmake_minimum_required(VERSION 3.26)
project(auta)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(auta main.cpp
        Database.h)
