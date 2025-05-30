#pragma once

#include "Bonus.hpp"

class BonusSave : public Bonus  //Ball bounces from bottom once
{
public:
    BonusSave(float x, float y);

    void applyEffect(Object &obj) override;
};