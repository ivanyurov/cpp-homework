#pragma once

#include "Object.hpp"
#include "Paddle.hpp"

class Bonus : public Object
{
public:
    sf::Vector2f velocity;

    Bonus(float x, float y, float width, float height, sf::Color color);

    void onTouch(Object &other) override;
    void update(float dt) override;

    virtual void applyEffect(Object &obj) = 0;
};
