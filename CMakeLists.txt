cmake_minimum_required(VERSION 3.7)
project(nanomites C CXX)
set(CMAKE_CXX_STANDARD 14)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_executable(nanomites src/main.cpp src/Parent.cpp src/Child.cpp)
set_target_properties(nanomites PROPERTIES
    CXX_STANDARD 17)

