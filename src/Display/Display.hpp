#pragma once

class Display
{
public:
    virtual ~Display() = default;

    virtual void show() = 0;
    virtual void hide() = 0;
};
