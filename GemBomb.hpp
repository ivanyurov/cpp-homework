#pragma once
#include "Gem.hpp"

class GemBomb : public Gem
{
public:
    GemBomb(GemColor color);
    void onMatched(std::vector<std::vector<std::shared_ptr<Gem>>> &grid, int row, int col) override;
};
