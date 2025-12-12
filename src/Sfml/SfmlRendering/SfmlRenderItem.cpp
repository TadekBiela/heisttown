#include "SfmlRenderItem.hpp"

SfmlRenderItem::SfmlRenderItem(
    sf::RenderTarget& inputTarget,
    const SceneItemId& inputId,
    const sf::Texture& texture,
    Position position,
    Rotation rotation
)
    : target(inputTarget)
    , id(inputId)
{
    sprite.setTexture(texture);
    auto textureSize { texture.getSize() };
    sprite.setOrigin({ textureSize.x / 2, textureSize.y / 2 });
    sprite.setRotation(rotation);
    sprite.setPosition({ position.x, position.y });
}

void SfmlRenderItem::render()
{
    target.draw(sprite);
}

SceneItemId SfmlRenderItem::getId() const
{
    return id;
}

void SfmlRenderItem::setPosition(Position position)
{
    sprite.setPosition({ position.x, position.y });
}

Position SfmlRenderItem::getPosition() const
{
    const auto sfPosition { sprite.getPosition() };
    return Position { sfPosition.x, sfPosition.y };
}

void SfmlRenderItem::setRotation(Rotation rotation)
{
    sprite.setRotation(rotation);
}

Rotation SfmlRenderItem::getRotation() const
{
    return sprite.getRotation();
}
