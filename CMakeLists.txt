cmake_minimum_required(VERSION 3.16)
project(GEMS)

set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "C:/VScode/libs/SFML/include")
set(SFML_LIB_DIR "C:/VScode/libs/SFML/lib")

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIB_DIR})

add_executable(GEMS
    main.cpp
    Game.cpp
    Gem.cpp
    GemBomb.cpp
    GemPaint.cpp
)

target_link_libraries(GEMS
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
