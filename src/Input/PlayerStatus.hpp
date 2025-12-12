#pragma once

struct FieldOfView
{
    float horizontal;
    float vertical;

    bool operator==(const FieldOfView& fov) const
    {
        return (horizontal == fov.horizontal and vertical == fov.vertical);
    }
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
    FieldOfView fov { 1000.0F, 800.0F };
    Direction moveDirection { Direction::FRONT };
    Velocity moveVelocity { 0.0F };
    Direction sightDirection { Direction::FRONT };
    Action currentAction { Action::NONE };

    bool operator==(const PlayerStatus& status) const
    {
        return (
            fov == status.fov and
            moveDirection == status.moveDirection and
            moveVelocity == status.moveVelocity and
            sightDirection == status.sightDirection and
            currentAction == status.currentAction
        );
    }
};
