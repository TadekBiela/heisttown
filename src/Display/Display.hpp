#pragma once

#include "Displayable.hpp"

class Display
{
public:
    virtual ~Display() = default;

    virtual void add(std::weak_ptr<Displayable> displayable) = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
};
