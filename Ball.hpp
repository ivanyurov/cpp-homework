#pragma once

#include "Object.hpp"
#include "Paddle.hpp"

class Ball : public Object
{
public:
    bool toStick = 0;   // for BonusStick
    bool toSave = 0;    // for BonusSave
    float randomTime = -1.f;    // for BonusRandom
    sf::CircleShape circleShape;
    sf::Vector2f velocity;

    Ball(float x, float y, float radius, sf::Color color);

    void onTouch(Object &other) override;
    void update(float dt) override;
    void draw(sf::RenderWindow &window) const override;
    void stick(const Paddle &paddle);
    void increaseSpeed(float factor);
    sf::FloatRect getBounds() const;
};