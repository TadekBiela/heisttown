#pragma once

#include "SceneItem.hpp"

class SceneItemFactory
{
public:
    virtual ~SceneItemFactory() = default;

    [[nodiscard]] virtual SceneItem create(
        const SceneItemType& type,
        const Position& position,
        const Rotation& rotation
    );

protected:
    virtual SceneItemId getNextSceneItemId();

private:
    inline static SceneItemId idCounter { 0 };
};
