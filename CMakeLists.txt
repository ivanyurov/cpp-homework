cmake_minimum_required(VERSION 3.10)
project(Wrapper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(test_engine
    tests/main.cpp
    src/Wrapper.cpp
    src/Engine.cpp
)