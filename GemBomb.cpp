#include "GemBomb.hpp"
#include <random>
#include <algorithm>

GemBomb::GemBomb(GemColor color) : Gem(color)
{
    shape.setOutlineThickness(3.f);
    shape.setOutlineColor(sf::Color::Black);
}

void GemBomb::onMatched(std::vector<std::vector<std::shared_ptr<Gem>>> &grid, int row, int col)
{
    Gem::onMatched(grid, row, col);

    int rows = grid.size();
    int cols = grid[0].size();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distRow(0, rows - 1);
    std::uniform_int_distribution<> distCol(0, cols - 1);

    int destroyed = 0;
    while (destroyed < 5)
    {
        int r = distRow(gen);
        int c = distCol(gen);

        if (grid[r][c])
        {
            grid[r][c] = nullptr;
            destroyed++;
        }
    }
}
