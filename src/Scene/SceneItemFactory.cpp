#include "SceneItemFactory.hpp"

SceneItem SceneItemFactory::create(
    const SceneItemType& type,
    const Position& position,
    const Rotation& rotation
)
{
    return SceneItem { getNextSceneItemId(), type, position, rotation };
}

SceneItemId SceneItemFactory::getNextSceneItemId()
{
    return idCounter++;
}
