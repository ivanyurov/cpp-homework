#pragma once

#include "Bonus.hpp"

class BonusSpeed : public Bonus //random speed change
{
public:
    BonusSpeed(float x, float y);

    void onTouch(Object &other) override;
    void applyEffect(Object &obj) override;
};