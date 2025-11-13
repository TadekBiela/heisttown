#pragma once

#include "GameObject.hpp"
#include <memory>

class GameObjectFactory
{
public:
    virtual ~GameObjectFactory() = default;

    [[nodiscard]] virtual std::shared_ptr<GameObject> create(Position position, Rotation rotation) const = 0;
};
