add_executable(calc
    parser.cpp
    evaluator.cpp
    plugin_loader.cpp
    main.cpp
)

target_include_directories(calc PRIVATE
    ${CMAKE_SOURCE_DIR}/src/api
    ${CMAKE_SOURCE_DIR}/src/calc
)

set_target_properties(calc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)