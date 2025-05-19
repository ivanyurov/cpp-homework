#pragma once
#include "Gem.hpp"

class GemPaint : public Gem
{
public:
    GemPaint(GemColor color);
    void onMatched(std::vector<std::vector<std::shared_ptr<Gem>>> &grid, int row, int col) override;
};
