#pragma once

using GoId = unsigned int;

enum class GoType
{
    PLAYER
};

struct Position
{
    float x;
    float y;

    bool operator==(const Position& position) const
    {
        return (x == position.x && y == position.y);
    }
};

using Rotation = float;

struct GameObject
{
    GoId id;
    GoType type;
    Position position;
    Rotation rotation;
};
