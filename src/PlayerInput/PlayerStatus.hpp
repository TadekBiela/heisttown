#pragma once

enum class Direction : char
{
    FRONT,
    FRONT_RIGHT,
    RIGHT,
    BACK_RIGHT,
    BACK,
    BACK_LEFT,
    LEFT,
    FRONT_LEFT
};

using Velocity = float;

enum class Action : char
{
    ATTACK,
    USE,
    NONE
};

struct PlayerStatus
{
    Direction moveDirection { Direction::FRONT };
    Velocity moveVelocity { 0.0 };
    Direction sightDirection { Direction::FRONT };
    Action currentAction { Action::NONE };
};
