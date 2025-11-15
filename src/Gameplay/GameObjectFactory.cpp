#include "GameObjectFactory.hpp"

GameObject GameObjectFactory::create(
    const GoType& type,
    const Position& position,
    const Rotation& rotation
) const
{
    return GameObject { idCounter++, type, position, rotation };
}
