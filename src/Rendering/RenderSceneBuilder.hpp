#pragma once

#include "RenderItem.hpp"
#include <SceneUpdate.hpp>

class RenderSceneBuilder
{
public:
    virtual ~RenderSceneBuilder() = default;

    virtual void build(const SceneUpdate& sceneUpdate) = 0;
    virtual RenderItems popRenderItems() = 0;
};
