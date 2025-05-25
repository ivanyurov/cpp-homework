#pragma once

#include "Bonus.hpp"

class BonusSize : public Bonus  // changes paddle size
{
public:
    BonusSize(float x, float y);

    void onTouch(Object &other) override;
    void applyEffect(Object &obj) override;
};