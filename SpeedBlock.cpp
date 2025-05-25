#include "SpeedBlock.hpp"
#include "Ball.hpp"

SpeedBlock::SpeedBlock(float x, float y, float width, float height)
    : Block(x, y, width, height, sf::Color::Yellow) {}

void SpeedBlock::onTouch(Object &other)
{
    if (Ball *ball = dynamic_cast<Ball *>(&other))
    {
        ball->increaseSpeed(speedFactor);
        Block::onTouch(other);
    }
}