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
    ~SfmlRenderItem() = default;

    void render() override;
    SceneItemId getId() const override;
    void setPosition(Position position) override;
    Position getPosition() const override;
    void setRotation(Rotation rotation) override;
    Rotation getRotation() const override;

private:
    sf::RenderTarget& target;
    const SceneItemId id;
    sf::Sprite sprite;
};
