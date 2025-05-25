#include "Paddle.hpp"

Paddle::Paddle(float x, float y, float width, float height, sf::Color color, float screenWidth)
    : Object(x, y, width, height, color), windowWidth(screenWidth) {}

void Paddle::onTouch(Object &other) {}

void Paddle::update(float dt) {}

void Paddle::moveLeft(float dt)
{
    sf::Vector2f pos = getPosition();
    pos.x -= moveSpeed * dt;
    if (pos.x < 0)
    {
        pos.x = 0;
    }
    setPosition(pos.x, pos.y);
}

void Paddle::moveRight(float dt)
{
    sf::Vector2f pos = getPosition();
    pos.x += moveSpeed * dt;
    if (pos.x + getBounds().width > windowWidth)
    {
        pos.x = windowWidth - getBounds().width;
    }
    setPosition(pos.x, pos.y);
}

void Paddle::changeSize(float newWidth)
{
    sf::Vector2f pos = getPosition();
    shape.setSize(sf::Vector2f(newWidth, shape.getSize().y));
    if (pos.x + newWidth > windowWidth)
    {
        setPosition(windowWidth - newWidth, pos.y);
    }
}