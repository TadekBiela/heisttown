#pragma once

#include <RenderItem.hpp>
#include <SceneItem.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class SfmlRenderItem : public RenderItem
{
public:
    SfmlRenderItem(
        sf::RenderTarget& inputTarget,
        const SceneItemId& inputId,
        const sf::Texture& texture,
        Position position,
        Rotation rotation
    );
    ~SfmlRenderItem() override = default;

    void render() override;
    SceneItemId getId() const;
    void setPosition(Position position);
    Position getPosition() const;
    void setRotation(Rotation rotation);
    Rotation getRotation() const;

private:
    sf::RenderTarget& target;
    const SceneItemId id;
    sf::Sprite sprite;
};
