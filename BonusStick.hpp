#pragma once

#include "Bonus.hpp"

class BonusStick : public Bonus // next collision betwen ball and paddle leads to sticking
{
public:
    BonusStick(float x, float y);

    void applyEffect(Object &obj) override;
};