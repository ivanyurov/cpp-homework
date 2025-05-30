#pragma once

#include "Object.hpp"

class Paddle : public Object
{
public:
    float moveSpeed = 700.f;
    const float windowWidth;

    Paddle(float x, float y, float width, float height, sf::Color color, float screenWidth);

    void onTouch(Object &other) override;
    void update(float dt) override;
    void moveLeft(float dt);
    void moveRight(float dt);
    void changeSize(float newWidth);
};