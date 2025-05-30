#pragma once

#include "Object.hpp"

class Block : public Object
{
public:
    int health;

    Block(float x, float y, float width, float height, sf::Color color, int hp = 1);

    void onTouch(Object &other) override;
    void update(float dt) override;

    virtual class Bonus *onBreak() { return nullptr; }
};