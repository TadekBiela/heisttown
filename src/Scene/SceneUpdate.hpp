#pragma once

#include "SceneItem.hpp"
#include <string>
#include <vector>

using MapName = std::string;

struct SceneUpdate
{
    MapName mapName;
    Position playerGlobalPosition;
    SceneItems sceneItems;
};
