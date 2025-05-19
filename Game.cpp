#include "Game.hpp"
#include "GemPaint.hpp"
#include "GemBomb.hpp"
#include <random>
#include <algorithm>
#include <set>
#include <iostream>

Game::Game() : window(sf::VideoMode(gridSize * tileSize, gridSize * tileSize), "GEMS Game")
{
    initGrid();
}

void Game::initGrid()
{
    grid.resize(gridSize, std::vector<std::shared_ptr<Gem>>(gridSize));
    for (int r = 0; r < gridSize; ++r)
    {
        for (int c = 0; c < gridSize; ++c)
        {
            GemColor color = getRandomColor();
            grid[r][c] = createRandomGem(color);
            grid[r][c]->setPosition(c * tileSize, r * tileSize);
        }
    }
}

void Game::run()
{
    while (window.isOpen())
    {
        handleInput();
        update();

        window.clear();
        drawGrid();
        window.display();
    }
}

void Game::handleInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            int x = event.mouseButton.x / tileSize;
            int y = event.mouseButton.y / tileSize;

            if (x >= 0 && x < gridSize && y >= 0 && y < gridSize)
            {
                if (firstSelection.x == -1)
                {
                    firstSelection = {x, y};
                }
                else
                {
                    sf::Vector2i second = {x, y};
                    if (isAdjacent(firstSelection, second))
                    {
                        swapGems(firstSelection, second);
                        if (checkMatches())
                        {
                            update();
                        }
                        else
                        {
                            swapGems(firstSelection, second);
                        }
                    }
                    firstSelection = {-1, -1};
                }
            }
        }
    }
}

void Game::update()
{
    bool hasMatches = false;
    applyGravity();
    fillEmpty();
    do
    {
        hasMatches = checkMatches();
        if (hasMatches)
        {
            applyGravity();
            fillEmpty();
        }
    } while (hasMatches);
}

void Game::drawGrid()
{
    for (int r = 0; r < gridSize; ++r)
    {
        for (int c = 0; c < gridSize; ++c)
        {
            if (grid[r][c])
            {
                grid[r][c]->setPosition(c * tileSize, r * tileSize);
                window.draw(grid[r][c]->getShape());
            }
        }
    }
}

bool Game::isAdjacent(sf::Vector2i a, sf::Vector2i b)
{
    return (std::abs(a.x - b.x) + std::abs(a.y - b.y)) == 1;
}

void Game::swapGems(sf::Vector2i a, sf::Vector2i b)
{
    std::swap(grid[a.y][a.x], grid[b.y][b.x]);
}

bool Game::checkMatches()
{
    bool found = false;
    std::vector<std::vector<bool>> visited(gridSize, std::vector<bool>(gridSize, false));
    std::set<std::pair<int, int>> toDestroy;

    auto dfs = [&](int r, int c, GemColor color, std::vector<std::pair<int, int>> &cluster, auto &dfs_ref) // dfs for finding all blocks with the same color and common borders
    {
        if (r < 0 || r >= gridSize || c < 0 || c >= gridSize || visited[r][c] || !grid[r][c] || grid[r][c]->getColor() != color)
            return;

        visited[r][c] = true;
        cluster.push_back({r, c});

        dfs_ref(r - 1, c, color, cluster, dfs_ref);
        dfs_ref(r + 1, c, color, cluster, dfs_ref);
        dfs_ref(r, c - 1, color, cluster, dfs_ref);
        dfs_ref(r, c + 1, color, cluster, dfs_ref);
    };

    for (int r = 0; r < gridSize; ++r)
    {
        for (int c = 0; c < gridSize; ++c)
        {
            if (!visited[r][c] && grid[r][c])
            {
                std::vector<std::pair<int, int>> cluster;
                GemColor color = grid[r][c]->getColor();
                dfs(r, c, color, cluster, dfs);

                if (cluster.size() >= 3)
                {
                    found = true;
                    for (const auto &pos : cluster)
                    {
                        toDestroy.insert(pos);
                    }
                }
            }
        }
    }

    for (auto [r, c] : toDestroy)
    {
        if (grid[r][c])
        {
            grid[r][c]->onMatched(grid, r, c);
            grid[r][c] = nullptr;
        }
    }

    return found;
}

void Game::applyGravity()
{
    for (int c = 0; c < gridSize; ++c)
    {
        for (int r = gridSize - 1; r >= 0; --r)
        {
            if (!grid[r][c])
            {
                for (int above = r - 1; above >= 0; --above)
                {
                    if (grid[above][c])
                    {
                        grid[r][c] = grid[above][c];
                        grid[above][c] = nullptr;
                        break;
                    }
                }
            }
        }
    }
}

void Game::fillEmpty()
{
    for (int r = 0; r < gridSize; ++r)
    {
        for (int c = 0; c < gridSize; ++c)
        {
            if (!grid[r][c])
            {
                GemColor color = getRandomColor();
                grid[r][c] = createRandomGem(color);
                grid[r][c]->setPosition(c * tileSize, r * tileSize);
            }
        }
    }
}

GemColor Game::getRandomColor() const
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, 6);
    return static_cast<GemColor>(dist(gen));
}

std::shared_ptr<Gem> Game::createRandomGem(GemColor color)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> chance(0.f, 1.f);

    float roll = chance(gen);
    if (roll < bonusChance / 2.f)
    {
        return std::make_shared<GemBomb>(color);
    }
    else if (roll < bonusChance)
    {
        return std::make_shared<GemPaint>(color);
    }
    else
    {
        return std::make_shared<Gem>(color);
    }
}
