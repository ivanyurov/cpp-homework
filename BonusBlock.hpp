#pragma once

#include "Block.hpp"
#include "Bonus.hpp"

class BonusBlock : public Block // Block that drops bonuses on break
{
public:
    BonusBlock(float x, float y, float width, float height);

    void onTouch(Object &other) override;

    Bonus *onBreak() override;
};