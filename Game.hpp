#pragma once

#include "Gem.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Game
{
private:
    const int gridSize = 8;
    const int tileSize = 64;
    const float bonusChance = 0.05f;

    std::vector<std::vector<std::shared_ptr<Gem>>> grid;
    sf::RenderWindow window;

    sf::Vector2i firstSelection = {-1, -1};
    bool swapping = false;

    void initGrid();
    void drawGrid();
    void handleInput();
    void update();

    bool isAdjacent(sf::Vector2i a, sf::Vector2i b);
    void swapGems(sf::Vector2i a, sf::Vector2i b);
    bool checkMatches();
    void applyGravity();
    void fillEmpty();
    GemColor getRandomColor() const;
    std::shared_ptr<Gem> createRandomGem(GemColor color);

public:
    Game();
    void run();
};
