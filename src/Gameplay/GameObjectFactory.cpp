#include "GameObjectFactory.hpp"

GameObject GameObjectFactory::create(
    const GoType& type,
    const Position& position,
    const Rotation& rotation
)
{
    return GameObject { getNextGoId(), type, position, rotation };
}

GoId GameObjectFactory::getNextGoId()
{
    return idCounter++;
}
