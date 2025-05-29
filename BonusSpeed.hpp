#pragma once

#include "Bonus.hpp"

class BonusSpeed : public Bonus //random speed change
{
public:
    BonusSpeed(float x, float y);

    void applyEffect(Object &obj) override;
};