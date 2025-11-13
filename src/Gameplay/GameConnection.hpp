#pragma once

#include <functional>

enum class GameCommand : char
{
    Pause = 0,
    NoCommand = 1
};

using GameConnection = std::function<void(const GameCommand&)>;
