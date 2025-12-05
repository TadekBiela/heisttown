#pragma once

#include <memory>
#include <vector>

class RenderTarget;

class RenderItem
{
public:
    virtual ~RenderItem() = default;

    virtual void render() = 0;
};

using RenderItems = std::vector<std::unique_ptr<RenderItem>>;
