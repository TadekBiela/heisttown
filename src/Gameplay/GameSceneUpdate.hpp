#pragma once

#include "GameObject.hpp"
#include <memory>
#include <vector>

using GameObjects = std::vector<std::shared_ptr<GameObject>>;

struct GameSceneUpdate
{
    GameObjects gameObjects;
};
