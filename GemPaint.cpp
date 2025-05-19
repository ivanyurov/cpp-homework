#include "GemPaint.hpp"
#include <algorithm>
#include <random>
#include <set>

GemPaint::GemPaint(GemColor color) : Gem(color)
{
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(3);
}

void GemPaint::onMatched(std::vector<std::vector<std::shared_ptr<Gem>>> &grid, int row, int col)
{
    Gem::onMatched(grid, row, col);

    static const std::vector<std::pair<int, int>> candidates = {
        {-2, 0}, {-2, 1}, {-1, 2}, {0, 2}, {1, 2}, {2, 1}, {2, 0}, {2, -1}, {1, -2}, {0, -2}, {-1, -2}, {-2, -1}, {-2, -2}, {-1, -1}, {1, 1}, {1, -1}}; // all possible candidates for painting

    int rows = grid.size();
    int cols = grid[0].size();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, candidates.size() - 1);

    int painted = 0;
    std::set<std::pair<int, int>> used;

    while (painted < 2)
    {
        auto [dy, dx] = candidates[dist(gen)];
        int r = row + dy;
        int c = col + dx;

        if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] && used.insert({r, c}).second)
        {
            grid[r][c] = std::make_shared<Gem>(color);
            ++painted;
        }
    }
}
