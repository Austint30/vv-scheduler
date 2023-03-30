
cmake_minimum_required(VERSION 3.13.0)

project(scheduler)

set(CMAKE_BUILD_TYPE Debug)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/simulator.cpp
    src/scheduler/sts.cpp
    src/scheduler/output.cpp
)