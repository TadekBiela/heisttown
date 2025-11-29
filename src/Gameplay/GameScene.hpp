#pragma once

#include "GameSceneUpdate.hpp"

class GameScene
{
public:
    virtual ~GameScene() = default;

    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void update(const GameSceneUpdate& sceneUpdate) = 0;
};
