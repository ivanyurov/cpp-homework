#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Object.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Block.hpp"
#include "Bonus.hpp"

class Game
{
public:
    Game();
    void run();

private:
    const float windowWidth = 800.f;
    const float windowHeight = 600.f;
    int score = 0;
    float basePaddleWidth = 100.f;
    void processEvents(float dt);
    void update(float dt);
    void render();
    void handleCollisions();
    void setupLevel();

    sf::RenderWindow window;
    std::unique_ptr<Ball> ball;
    std::unique_ptr<Paddle> paddle;
    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Bonus>> bonuses;
};