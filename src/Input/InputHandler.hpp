#pragma once
#include "InputEvent.hpp"

class InputHandler
{
public:
    virtual ~InputHandler() = default;

    virtual bool handle(const InputEvent& event) = 0;
};
