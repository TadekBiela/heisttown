#pragma once

#include "SceneItem.hpp"
#include <memory>
#include <vector>

class RenderItem
{
public:
    virtual ~RenderItem() = default;

    virtual void render() = 0;
    virtual SceneItemId getId() const = 0;
    virtual void setPosition(Position position) = 0;
    virtual Position getPosition() const = 0;
    virtual void setRotation(Rotation rotation) = 0;
    virtual Rotation getRotation() const = 0;
};

using RenderItems = std::vector<std::unique_ptr<RenderItem>>;
