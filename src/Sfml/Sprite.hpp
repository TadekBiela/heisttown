#pragma once

#include "Drawable.hpp"
#include <SceneItem.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Sprite : public Drawable
{
public:
    Sprite(const SceneItemId inputId, const sf::Texture& texture, Position position, Rotation rotation);
    virtual ~Sprite() = default;

    virtual void draw(sf::RenderTarget& target) const override;
    virtual SceneItemId getId() const;
    virtual void setPosition(Position position);
    virtual void setRotation(Rotation rotation);

private:
    const SceneItemId id;
    sf::Sprite sprite;
};
