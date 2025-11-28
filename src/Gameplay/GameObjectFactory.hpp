#pragma once

#include "GameObject.hpp"

class GameObjectFactory
{
public:
    virtual ~GameObjectFactory() = default;

    [[nodiscard]] virtual GameObject create(
        const GoType& type,
        const Position& position,
        const Rotation& rotation
    );

protected:
    virtual GoId getNextGoId();

private:
    inline static GoId idCounter { 0 };
};
