#include "Gem.hpp"

Gem::Gem(GemColor color) : color(color)
{
    shape.setSize({64.f, 64.f});
    switch (color)
    {
    case GemColor::Red:
        shape.setFillColor(sf::Color::Red);
        break;
    case GemColor::Orange:
        shape.setFillColor(sf::Color(255, 165, 0));
        break;
    case GemColor::Yellow:
        shape.setFillColor(sf::Color::Yellow);
        break;
    case GemColor::Green:
        shape.setFillColor(sf::Color::Green);
        break;
    case GemColor::Blue:
        shape.setFillColor(sf::Color::Blue);
        break;
    case GemColor::Indigo:
        shape.setFillColor(sf::Color(75, 0, 130));
        break;
    case GemColor::Violet:
        shape.setFillColor(sf::Color(128, 0, 128));
        break;
    }
}

GemColor Gem::getColor() const
{
    return color;
}

const sf::RectangleShape &Gem::getShape() const
{
    return shape;
}

void Gem::setPosition(float x, float y)
{
    shape.setPosition(x, y);
}

void Gem::onMatched(std::vector<std::vector<std::shared_ptr<Gem>>> &, int, int)
{
    // does nothing, since it's basic gem
}
