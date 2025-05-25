#include "BonusSize.hpp"
#include "Paddle.hpp"

BonusSize::BonusSize(float x, float y)
    : Bonus(x, y, 30.f, 15.f, sf::Color::Green) {}

void BonusSize::onTouch(Object &other)
{
    if (Paddle *paddle = dynamic_cast<Paddle *>(&other))
    {
        applyEffect(*paddle);
    }
}

void BonusSize::applyEffect(Object &obj)
{
    Paddle *paddle = dynamic_cast<Paddle *>(&obj);
    paddle->changeSize(150.f);
    destroyed = true;
}