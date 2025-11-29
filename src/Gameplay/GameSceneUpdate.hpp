#pragma once

#include "GameObject.hpp"
#include <string>
#include <vector>

using MapName = std::string;

using GameObjects = std::vector<GameObject>;

struct GameSceneUpdate
{
    MapName mapName;
    Position playerGlobalPosition;
    GameObjects gameObjects;
};
