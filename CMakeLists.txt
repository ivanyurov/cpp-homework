cmake_minimum_required(VERSION 3.16)
project(ARCANOID)

set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "C:/VScode/libs/SFML/include")
set(SFML_LIB_DIR "C:/VScode/libs/SFML/lib")

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIB_DIR})

add_executable(ARCANOID
    main.cpp
    Game.cpp
    Ball.cpp
    Block.cpp
    Bonus.cpp
    BonusBlock.cpp
    BonusRandom.cpp
    BonusSave.cpp
    BonusSize.cpp
    BonusSpeed.cpp
    BonusStick.cpp
    IndestructibleBlock.cpp
    Paddle.cpp
    SpeedBlock.cpp
)

target_link_libraries(ARCANOID
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
