#include "BonusRandom.hpp"
#include "Ball.hpp"
#include <cmath>
#include <random>

BonusRandom::BonusRandom(float x, float y) : Bonus(x, y, 30.f, 15.f, sf::Color(0, 200, 100)) {}

void BonusRandom::onTouch(Object &other)
{
    applyEffect(other);
}

void BonusRandom::applyEffect(Object &obj)
{
    Ball *ball = dynamic_cast<Ball *>(&obj);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(1.0f, 5.0f);
    ball->randomTime = dist(gen);
    destroyed = true;
}