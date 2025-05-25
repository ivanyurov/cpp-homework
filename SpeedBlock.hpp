#pragma once

#include "Block.hpp"

class SpeedBlock : public Block
{
public:
    float speedFactor = 1.15f;

    SpeedBlock(float x, float y, float width, float height);

    void onTouch(Object &other) override;
};
