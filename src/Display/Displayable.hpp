#pragma once

#include <memory>

class Display;

class Displayable
{
public:
    ~Displayable() = default;

    virtual void display() const = 0;
};
