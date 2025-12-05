#pragma once

#include "RenderItem.hpp"

class RenderTarget
{
public:
    virtual ~RenderTarget() = default;

    virtual void render(const RenderItems& renderItems) = 0;
};
