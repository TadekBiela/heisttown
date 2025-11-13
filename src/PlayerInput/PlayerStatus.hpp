#pragma once

struct FieldOfView
{
    float horizontal;
    float vertical;
};

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
    FieldOfView fov { 1000, 800 };
    Direction moveDirection { Direction::FRONT };
    Velocity moveVelocity { 0.0 };
    Direction sightDirection { Direction::FRONT };
    Action currentAction { Action::NONE };
};
