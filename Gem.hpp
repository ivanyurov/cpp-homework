#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

enum class GemColor
{
    Red,
    Orange,
    Yellow,
    Green,
    Blue,
    Indigo,
    Violet
};

class Gem
{
protected:
    GemColor color;
    sf::RectangleShape shape;

public:
    Gem(GemColor color);
    virtual ~Gem() = default;

    GemColor getColor() const;
    const sf::RectangleShape &getShape() const;
    virtual void setPosition(float x, float y);

    virtual void onMatched(std::vector<std::vector<std::shared_ptr<Gem>>> &grid, int row, int col); // Each type has its' own reaction after matching
};
