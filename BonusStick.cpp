#include "BonusStick.hpp"
#include "Ball.hpp"
#include <cmath>

BonusStick::BonusStick(float x, float y)
    : Bonus(x, y, 30.f, 15.f, sf::Color(100, 100, 100)) {}

void BonusStick::applyEffect(Object &obj)
{
    Ball *ball = dynamic_cast<Ball *>(&obj);
    ball->toStick = 1;
    destroyed = true;
}