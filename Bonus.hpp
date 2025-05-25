#pragma once

#include "Object.hpp"
#include "Paddle.hpp"

class Bonus : public Object
{
public:
    sf::Vector2f velocity;

    Bonus(float x, float y, float width, float height, sf::Color color);

    void onTouch(Object &other) override = 0;
    void update(float dt) override;

    virtual void applyEffect(Object &obj) = 0;
};
