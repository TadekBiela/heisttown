#pragma once

#include "SfmlRenderItem.hpp"
#include "TextureFile.hpp"
#include <FilesStorage.hpp>
#include <SceneItem.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>

class SfmlRenderItemFactory
{
public:
    SfmlRenderItemFactory(
        sf::RenderTarget& inputTarget,
        std::shared_ptr<FilesStorage<TextureFile>> inputTextureStorage
    );
    virtual ~SfmlRenderItemFactory() = default;

    [[nodiscard]] virtual std::unique_ptr<SfmlRenderItem> create(const SceneItemType& type, const Position& position, const Rotation& rotation);

protected:
    virtual SceneItemId getNextSceneItemId();

private:
    inline static SceneItemId idCounter { 0 };
    sf::RenderTarget& target;
    std::shared_ptr<FilesStorage<TextureFile>> textureStorage;

    [[nodiscard]] const sf::Texture& getTexture(const SceneItemType& type) const;
    static std::string translateTypeToTextureName(const SceneItemType& type);
};
