#pragma once

#include "GameSceneUpdate.hpp"

class GameScene
{
public:
    virtual ~GameScene() = default;

    virtual void update(const GameSceneUpdate& sceneUpdate) = 0;
};
