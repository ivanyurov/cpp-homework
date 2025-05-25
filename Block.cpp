#include "Block.hpp"
#include "Ball.hpp"

Block::Block(float x, float y, float width, float height, sf::Color color, int hp)
    : Object(x, y, width, height, color), health(hp) {}

void Block::onTouch(Object &other)
{
    if (dynamic_cast<Ball *>(&other))
    {
        health--;
        if (health <= 0)
        {
            destroyed = true;
        }
    }
}

void Block::update(float dt) {};