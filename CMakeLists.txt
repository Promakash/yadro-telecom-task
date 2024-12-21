cmake_minimum_required(VERSION 3.10)

project(yadro-telecom-task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(include)

set(SOURCE_FILES
        source/main.cpp
        source/club.cpp
        source/event.cpp
        source/event_handler.cpp
        source/client.cpp
        source/table.cpp
)

add_executable(task ${SOURCE_FILES})
