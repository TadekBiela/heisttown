#pragma once

#include "Drawable.hpp"
#include <GameObject.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Sprite : public Drawable
{
public:
    Sprite(const GoId inputId, const sf::Texture& texture, Position position, Rotation rotation);
    virtual ~Sprite() = default;

    virtual void draw(sf::RenderTarget& target) const override;
    virtual GoId getId() const;
    virtual void setPosition(Position position);
    virtual void setRotation(Rotation rotation);

private:
    const GoId id;
    sf::Sprite sprite;
};
