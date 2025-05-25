#include "Ball.hpp"
#include "Block.hpp"
#include "Paddle.hpp"
#include <cmath>

Ball::Ball(float x, float y, float radius, sf::Color color)
    : Object(x, y, radius * 2, radius * 2, color)
{
    velocity = {0.f, 0.f};
    circleShape.setPosition(x, y);
    circleShape.setRadius(radius);
    circleShape.setFillColor(color);
    circleShape.setOutlineColor(sf::Color::Black);
    circleShape.setOutlineThickness(1.f);
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(radius * 2, radius * 2));
}

void Ball::stick(const Paddle &paddle)  //sticks to paddle
{
    this->velocity = {0.f, 0.f};
    float paddleCenterX = paddle.getPosition().x + paddle.getSize().x / 2.f;
    this->circleShape.setPosition(paddleCenterX - this->circleShape.getRadius(),
                                  paddle.getPosition().y - this->circleShape.getRadius() * 2);
    this->shape.setPosition(circleShape.getPosition());
}

void Ball::increaseSpeed(float factor)
{
    velocity *= factor;
}

void Ball::onTouch(Object &other)
{
    const float epsilon = 2.f;

    sf::FloatRect ballBounds = this->getBounds();
    sf::FloatRect otherBounds = other.getBounds();

    float overlapLeft = ballBounds.left + ballBounds.width - otherBounds.left;
    float overlapRight = otherBounds.left + otherBounds.width - ballBounds.left;
    float overlapTop = ballBounds.top + ballBounds.height - otherBounds.top;
    float overlapBottom = otherBounds.top + otherBounds.height - ballBounds.top;

    bool fromLeft = overlapLeft < overlapRight;
    bool fromTop = overlapTop < overlapBottom;

    float minOverlapX = fromLeft ? overlapLeft : overlapRight;
    float minOverlapY = fromTop ? overlapTop : overlapBottom;

    if (minOverlapX < minOverlapY)
    {
        velocity.x = -velocity.x;

        float newX = fromLeft ? otherBounds.left - ballBounds.width - epsilon
                              : otherBounds.left + otherBounds.width + epsilon;

        setPosition(newX, getPosition().y);
    }
    else
    {
        velocity.y = -velocity.y;

        float newY = fromTop ? otherBounds.top - ballBounds.height - epsilon
                             : otherBounds.top + otherBounds.height + epsilon;

        setPosition(getPosition().x, newY);
    }

    if (dynamic_cast<Paddle *>(&other) && this->toStick)    //for BonusStick
    {
        this->toStick = 0;
        stick(*dynamic_cast<Paddle *>(&other));
    }
}

void Ball::update(float dt)
{
    if (velocity.x != 0.f || velocity.y != 0.f)
    {
        sf::Vector2f pos = circleShape.getPosition();
        pos += velocity * dt;
        circleShape.setPosition(pos);
        shape.setPosition(pos);
    }
}

void Ball::draw(sf::RenderWindow &window) const
{
    if (!destroyed)
    {
        window.draw(circleShape);
    }
}

sf::FloatRect Ball::getBounds() const
{
    return circleShape.getGlobalBounds();
}