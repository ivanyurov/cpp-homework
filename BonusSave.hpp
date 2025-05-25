#pragma once

#include "Bonus.hpp"

class BonusSave : public Bonus  //Ball bounces from bottom once
{
public:
    BonusSave(float x, float y);

    void onTouch(Object &other) override;
    void applyEffect(Object &obj) override;
};