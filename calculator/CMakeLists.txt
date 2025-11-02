cmake_minimum_required(VERSION 3.15)
project(CalculatorWithPlugins LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/plugins)

add_subdirectory(src/calc)
add_subdirectory(src/plugins/sin)
add_subdirectory(src/plugins/cos)
add_subdirectory(src/plugins/tg)
add_subdirectory(src/plugins/ctg)
add_subdirectory(src/plugins/ln)
add_subdirectory(src/plugins/log)

