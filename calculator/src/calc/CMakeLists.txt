add_executable(calc
    parser.cpp
    evaluator.cpp
    plugin_loader.cpp
    main.cpp
)

target_include_directories(calc PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)