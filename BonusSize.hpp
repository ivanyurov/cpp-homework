#pragma once

#include "Bonus.hpp"

class BonusSize : public Bonus // changes paddle size
{
public:
    BonusSize(float x, float y);

    void applyEffect(Object &obj) override;
};