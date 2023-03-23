
cmake_minimum_required(VERSION 3.13.0)

project(scheduler)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/task.cpp
)