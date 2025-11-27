#include "SpriteFactory.hpp"

SpriteFactory::SpriteFactory(std::shared_ptr<FilesStorage<TextureFile>> inputTextureStorage)
    : goIdCounter(0)
    , textureStorage(std::move(inputTextureStorage))
{
}

std::unique_ptr<Sprite> SpriteFactory::create(const GoType& type, const Position& position, const Rotation& rotation)
{
    return std::make_unique<Sprite>(goIdCounter++, getTexture(type), position, rotation);
}

const sf::Texture& SpriteFactory::getTexture(const GoType& type) const
{
    return textureStorage->getFile(translateTypeToTextureName(type)).getTexture();
}

std::string SpriteFactory::translateTypeToTextureName(const GoType& type)
{
    switch (type)
    {
        case (GoType::PLAYER):
        {
            return "player";
        }
        default:
            return "default";
    }
}
