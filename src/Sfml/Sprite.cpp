#include "Sprite.hpp"

Sprite::Sprite(const sf::Texture& texture, Position position, Rotation rotation)
{
    sprite.setTexture(texture);
    sprite.setPosition({ position.x, position.y });
    sprite.setRotation(rotation);
}

void Sprite::draw(sf::RenderTarget& target) const
{
    target.draw(sprite);
}

void Sprite::setPosition(Position position)
{
    sprite.setPosition({ position.x, position.y });
}

void Sprite::setRotation(Rotation rotation)
{
    sprite.setRotation(rotation);
}
