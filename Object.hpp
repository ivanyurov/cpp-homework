#pragma once

#include <SFML/Graphics.hpp>

class Object // base class
{
public:
    sf::RectangleShape shape;
    bool destroyed = false;

    Object(float x, float y, float width, float height, sf::Color color);
    virtual ~Object() = default;

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    sf::Vector2f getSize() const;

    virtual void onTouch(Object &other) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow &window) const;
};