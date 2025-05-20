#pragma once

class GameDisplay
{
public:
    virtual ~GameDisplay() = default;

    virtual void show() = 0;
    virtual void hide() = 0;
};
