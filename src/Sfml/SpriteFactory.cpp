#include "SpriteFactory.hpp"

SpriteFactory::SpriteFactory(std::shared_ptr<FilesStorage<TextureFile>> inputTextureStorage)
    : goIdCounter(0)
    , textureStorage(std::move(inputTextureStorage))
{
}

std::unique_ptr<Sprite> SpriteFactory::create(const SceneItemType& type, const Position& position, const Rotation& rotation)
{
    return std::make_unique<Sprite>(goIdCounter++, getTexture(type), position, rotation);
}

const sf::Texture& SpriteFactory::getTexture(const SceneItemType& type) const
{
    return textureStorage->getFile(translateTypeToTextureName(type)).getTexture();
}

std::string SpriteFactory::translateTypeToTextureName(const SceneItemType& type)
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
