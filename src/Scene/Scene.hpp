#pragma once

#include "SceneUpdate.hpp"

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void update(const SceneUpdate& sceneUpdate) = 0;
};
