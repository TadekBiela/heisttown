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
        const SceneItemId inputId,
        const sf::Texture& texture,
        Position position,
        Rotation rotation
    );
    virtual ~SfmlRenderItem() = default;

    virtual void render() override;
    virtual SceneItemId getId() const;
    virtual void setPosition(Position position);
    virtual void setRotation(Rotation rotation);

private:
    sf::RenderTarget& target;
    const SceneItemId id;
    sf::Sprite sprite;
};
