#include "BonusSpeed.hpp"
#include "Ball.hpp"
#include <random>

BonusSpeed::BonusSpeed(float x, float y)
    : Bonus(x, y, 30.f, 15.f, sf::Color::Blue) {}

void BonusSpeed::applyEffect(Object &obj)
{
    Ball *ball = dynamic_cast<Ball *>(&obj);
    if (ball->velocity.x != 0)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(0.67f, 1.5f);

        ball->velocity *= dist(gen);
        }
    destroyed = true;
}