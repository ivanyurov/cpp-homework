#include "IndestructibleBlock.hpp"

IndestructibleBlock::IndestructibleBlock(float x, float y, float width, float height)
    : Block(x, y, width, height, sf::Color(100, 100, 100), 999) {} // Серый цвет, много HP

void IndestructibleBlock::onTouch(Object &other) {}