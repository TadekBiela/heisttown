#pragma once

#include "InputEvent.hpp"
#include <vector>

class InputSource
{
public:
    virtual ~InputSource() = default;

    virtual std::vector<InputEvent> pollEvents() = 0;
};
