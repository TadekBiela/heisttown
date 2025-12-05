#pragma once

#include "RenderItem.hpp"

class RenderSceneBuilder
{
public:
    virtual ~RenderSceneBuilder() = default;

    virtual RenderItems getRenderItems() const = 0;
};
