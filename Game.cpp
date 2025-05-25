#define _USE_MATH_DEFINES

#include "Game.hpp"
#include "IndestructibleBlock.hpp"
#include "SpeedBlock.hpp"
#include "BonusBlock.hpp"
#include "BonusSize.hpp"
#include <random>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>

Game::Game() : window(sf::VideoMode(static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)), "Arkanoid SFML")
{
    window.setFramerateLimit(60);

    paddle = std::make_unique<Paddle>(windowWidth / 2 - basePaddleWidth / 2, windowHeight - 30.f, basePaddleWidth, 20.f, sf::Color::Red, windowWidth);
    ball = std::make_unique<Ball>(windowWidth / 2 - 10.f, windowHeight / 2 - 10.f, 10.f, sf::Color::White);

    setupLevel();
    ball->stick(*paddle);
}

void Game::setupLevel()
{
    blocks.clear();
    bonuses.clear();

    int blockWidth = 60;
    int blockHeight = 20;
    int padding = 5;
    int rows = 8;
    int cols = static_cast<int>(windowWidth / (blockWidth + padding));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            float x = j * (blockWidth + padding) + padding;
            float y = i * (blockHeight + padding) + padding + 50;

            if ((j == 2 || j == cols - 3) && i < 5)
            {
                blocks.push_back(std::make_unique<IndestructibleBlock>(x, y, blockWidth, blockHeight));
            }
            else if (j == 1 || j == cols - 2)
            {
                blocks.push_back(std::make_unique<SpeedBlock>(x, y, blockWidth, blockHeight));
            }
            else if (i % 3 == 0 || j % 3 == 0)
            {
                blocks.push_back(std::make_unique<BonusBlock>(x, y, blockWidth, blockHeight));
            }
            else
            {
                blocks.push_back(std::make_unique<Block>(x, y, blockWidth, blockHeight, sf::Color(150, 50, 150)));
            }
        }
    }
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        processEvents(deltaTime.asSeconds());
        update(deltaTime.asSeconds());
        render();
    }
}

void Game::processEvents(float dt)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (ball->velocity.x == 0.f && ball->velocity.y == 0.f)
        {
            ball->velocity.x = 300.f;
            ball->velocity.y = -300.f;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        paddle->moveLeft(dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        paddle->moveRight(dt);
    }

    if (ball->velocity.x == 0.f && ball->velocity.y == 0.f)
    {
        ball->stick(*paddle);
    }
}

void Game::update(float dt)
{
    ball->update(dt);
    paddle->update(dt);

    for (auto &bonus : bonuses)
    {
        bonus->update(dt);
    }

    sf::Vector2f ballPos = ball->circleShape.getPosition();
    sf::FloatRect ballBounds = ball->getBounds();

    if (ballPos.x < 0)
    {
        ball->velocity.x = std::abs(ball->velocity.x);
        ball->circleShape.setPosition(0, ballPos.y);
    }
    if (ballPos.x + ballBounds.width > windowWidth)
    {
        ball->velocity.x = -std::abs(ball->velocity.x);
        ball->circleShape.setPosition(windowWidth - ballBounds.width, ballPos.y);
    }
    if (ballPos.y < 0)
    {
        ball->velocity.y = std::abs(ball->velocity.y);
        ball->circleShape.setPosition(ballPos.x, 0);
    }

    if (ballPos.y + ballBounds.height > windowHeight)
    {
        if (ball->toSave)
        {
            ball->toSave = 0;
            ball->velocity.y = -std::abs(ball->velocity.y);
            ball->circleShape.setPosition(ballPos.x, windowHeight - ballBounds.height);
        }
        else
        {
            std::cout << "Ball Lost! Score: " << score << std::endl;
            ball->stick(*paddle);
            score = 0;
            paddle->changeSize(basePaddleWidth);
            bonuses.clear();
        }
    }

    if (ball->randomTime != -1.f)
    {
        ball->randomTime -= dt;
    }

    if (ball->randomTime != -1.f && ball->randomTime <= 0)
    {
        ball->randomTime = -1.f;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> angleDist(0.0f, 2 * M_PI);

        float angle = angleDist(gen);
        float vx = ball->velocity.x;
        float vy = ball->velocity.y;

        ball->velocity.x = vx * cos(angle) - vy * sin(angle);
        ball->velocity.y = vx * sin(angle) + vy * cos(angle);
    }

    handleCollisions();

    blocks.erase(std::remove_if(blocks.begin(), blocks.end(),
                                [](const std::unique_ptr<Block> &block)
                                {
                                    return block->destroyed;
                                }),
                 blocks.end());

    bonuses.erase(std::remove_if(bonuses.begin(), bonuses.end(),
                                 [this](const std::unique_ptr<Bonus> &bonus)
                                 {
                                     return bonus->destroyed || bonus->getPosition().y > this->windowHeight;
                                 }),
                  bonuses.end());

    bool won = true;
    for (const auto &block : blocks)
    {
        if (!dynamic_cast<IndestructibleBlock *>(block.get()))
        {
            won = false;
            break;
        }
    }
    if (won)
    {
        std::cout << "You Won! Score: " << score << std::endl;
        setupLevel();
        ball->stick(*paddle);
        score = 0;
    }
}

void Game::handleCollisions()
{
    sf::FloatRect ballBounds = ball->getBounds();
    sf::FloatRect paddleBounds = paddle->getBounds();

    if (ballBounds.intersects(paddleBounds))    //between ball and paddle
    {
        ball->onTouch(*paddle);
    }

    for (auto &block : blocks)  //between ball and blocks
    {
        if (!block->destroyed && ballBounds.intersects(block->getBounds()))
        {
            bool was_destroyed_before = block->destroyed;

            ball->onTouch(*block);
            block->onTouch(*ball);

            if (block->destroyed && !was_destroyed_before)
            {
                score += 1;
                std::cout << "Score: " << score << std::endl;

                if (Bonus *newBonus = block->onBreak())
                {
                    bonuses.push_back(std::unique_ptr<Bonus>(newBonus));
                }
            }
            break;
        }
    }

    for (auto &bonus : bonuses) //between paddle and bonuses
    {
        if (!bonus->destroyed && bonus->getBounds().intersects(paddle->getBounds()))
        {

            if (auto paddleBonus = dynamic_cast<BonusSize *>(bonus.get()))
            {
                paddleBonus->onTouch(*paddle);
            }
            else
            {
                bonus->onTouch(*ball);
            }
        }
    }
}

void Game::render()
{
    window.clear(sf::Color::Black);

    ball->draw(window);
    paddle->draw(window);
    for (const auto &block : blocks)
    {
        block->draw(window);
    }
    for (const auto &bonus : bonuses)
    {
        bonus->draw(window);
    }

    window.display();
}