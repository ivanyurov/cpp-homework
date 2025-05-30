#include "BonusSave.hpp"
#include "Ball.hpp"

BonusSave::BonusSave(float x, float y) : Bonus(x, y, 30.f, 15.f, sf::Color(150, 0, 100)) {}

void BonusSave::applyEffect(Object &obj)
{
    Ball *ball = dynamic_cast<Ball *>(&obj);
    ball->toSave = 1;
    destroyed = true;
}