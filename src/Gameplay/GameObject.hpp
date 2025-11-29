#pragma once

using GoId = unsigned int;

enum class GoType
{
    PLAYER
};

struct Position
{
    float x { 0.0F };
    float y { 0.0F };

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
