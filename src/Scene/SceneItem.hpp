#pragma once

#include <vector>

using SceneItemId = unsigned int;

enum class SceneItemType
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

struct SceneItem
{
    SceneItemId id;
    SceneItemType type;
    Position position;
    Rotation rotation;
};

using SceneItems = std::vector<SceneItem>;
