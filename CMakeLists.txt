cmake_minimum_required(VERSION 3.10)

project(yadro-telecom-task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Werror
)

include_directories(include)
include_directories(util)

set(SOURCE_FILES
        source/club.cpp
        source/event.cpp
        source/event_handler.cpp
        source/client.cpp
        source/table.cpp
        source/validator.cpp
        source/event_response.cpp
)

add_executable(task source/main.cpp ${SOURCE_FILES})

include(cmake/Utils.cmake)

include_catch2()

add_executable_test(test_validator tests/test_validator.cpp ${SOURCE_FILES})

target_compile_definitions(test_validator PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/tests/static")

add_executable_test(test_club tests/test_club.cpp ${SOURCE_FILES})

target_compile_definitions(test_club PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/tests/static")
