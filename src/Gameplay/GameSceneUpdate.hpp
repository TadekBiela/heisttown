#pragma once

#include "GameObject.hpp"
#include <vector>

using GameObjects = std::vector<GameObject>;

struct GameSceneUpdate
{
    GameObjects gameObjects;
};
