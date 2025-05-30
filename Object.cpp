#include "Object.hpp"

Object::Object(float x, float y, float width, float height, sf::Color color)
{
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.f);
}

sf::FloatRect Object::getBounds() const
{
    return shape.getGlobalBounds();
}

sf::Vector2f Object::getPosition() const
{
    return shape.getPosition();
}

void Object::setPosition(float x, float y)
{
    shape.setPosition(x, y);
}

sf::Vector2f Object::getSize() const
{
    return shape.getSize();
}

void Object::draw(sf::RenderWindow &window) const
{
    if (!destroyed)
    {
        window.draw(shape);
    }
}