#include "Bonus.hpp"

Bonus::Bonus(float x, float y, float width, float height, sf::Color color)
    : Object(x, y, width, height, color)
{
    velocity = {0.f, 200.f};
}

void Bonus::update(float dt)
{
    sf::Vector2f pos = getPosition();
    pos += velocity * dt;
    setPosition(pos.x, pos.y);
}