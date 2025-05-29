#pragma once

#include "Bonus.hpp"

class BonusRandom : public Bonus    //random direction change
{
public:
    BonusRandom(float x, float y);

    void applyEffect(Object &obj) override;
};