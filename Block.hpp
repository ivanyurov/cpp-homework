#pragma once

#include "Object.hpp"

class Block : public Object
{
public:
    int health;

    Block(float x, float y, float width, float height, sf::Color color, int hp = 1);

    virtual void onTouch(Object &other) override;
    virtual void update(float dt) override;

    virtual class Bonus *onBreak() { return nullptr; }
};