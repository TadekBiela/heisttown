#pragma once

#include <memory>
#include <vector>

class RenderItem
{
public:
    virtual ~RenderItem() = default;

    virtual void render() = 0;
};

using RenderItems = std::vector<std::shared_ptr<RenderItem>>;
