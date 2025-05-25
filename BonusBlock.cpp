#include "BonusBlock.hpp"
#include "BonusSize.hpp"
#include "BonusSpeed.hpp"
#include "BonusStick.hpp"
#include "BonusSave.hpp"
#include "BonusRandom.hpp"
#include <random>

BonusBlock::BonusBlock(float x, float y, float width, float height)
    : Block(x, y, width, height, sf::Color::Magenta) {}

void BonusBlock::onTouch(Object &other)
{
    Block::onTouch(other);
}

Bonus *BonusBlock::onBreak()    // switches between different bonuses
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 4);

    int bonus = dist(gen);
    switch (bonus)
    {
    case 0:
        return new BonusSize(getPosition().x + getSize().x / 2 - 15.f, getPosition().y);
        break;
    case 1:
        return new BonusSpeed(getPosition().x + getSize().x / 2 - 15.f, getPosition().y);
        break;
    case 2:
        return new BonusStick(getPosition().x + getSize().x / 2 - 15.f, getPosition().y);
        break;
    case 3:
        return new BonusSave(getPosition().x + getSize().x / 2 - 15.f, getPosition().y);
        break;
    case 4:
        return new BonusRandom(getPosition().x + getSize().x / 2 - 15.f, getPosition().y);
        break;
    }
    return nullptr;
}