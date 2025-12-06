#include "SfmlRenderItemFactory.hpp"

SfmlRenderItemFactory::SfmlRenderItemFactory(
    sf::RenderTarget& inputTarget,
    std::shared_ptr<FilesStorage<TextureFile>> inputTextureStorage
)
    : target(inputTarget)
    , textureStorage(std::move(inputTextureStorage))
{
}

std::unique_ptr<SfmlRenderItem> SfmlRenderItemFactory::create(const SceneItemType& type, const Position& position, const Rotation& rotation)
{
    return std::make_unique<SfmlRenderItem>(target, getNextSceneItemId(), getTexture(type), position, rotation);
}

SceneItemId SfmlRenderItemFactory::getNextSceneItemId()
{
    return idCounter++;
}

const sf::Texture& SfmlRenderItemFactory::getTexture(const SceneItemType& type) const
{
    return textureStorage->getFile(translateTypeToTextureName(type)).getTexture();
}

std::string SfmlRenderItemFactory::translateTypeToTextureName(const SceneItemType& type)
{
    switch (type)
    {
        case (SceneItemType::PLAYER):
        {
            return "player";
        }
        default:
            return "default";
    }
}
