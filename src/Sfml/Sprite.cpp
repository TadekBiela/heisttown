#include "Sprite.hpp"

Sprite::Sprite(const GoId inputId, const sf::Texture& texture, Position position, Rotation rotation)
    : id(inputId)
{
    sprite.setTexture(texture);
    sprite.setPosition({ position.x, position.y });
    sprite.setRotation(rotation);
}

void Sprite::draw(sf::RenderTarget& target) const
{
    target.draw(sprite);
}

GoId Sprite::getId() const
{
    return id;
}

void Sprite::setPosition(Position position)
{
    sprite.setPosition({ position.x, position.y });
}

void Sprite::setRotation(Rotation rotation)
{
    sprite.setRotation(rotation);
}
