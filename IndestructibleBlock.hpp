#pragma once

#include "Block.hpp"

class IndestructibleBlock : public Block
{
public:
    IndestructibleBlock(float x, float y, float width, float height);

    void onTouch(Object &other) override; // Переопределяем, чтобы ничего не делать
};
