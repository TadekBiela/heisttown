#include "SpriteFactory.hpp"

SpriteFactory::SpriteFactory(std::shared_ptr<FilesStorage<TextureFile>> inputTextureStorage)
    : goIdCounter(0)
    , textureStorage(std::move(inputTextureStorage))
{
}
#include <iostream>
std::unique_ptr<Sprite> SpriteFactory::create(const GoType& type, const Position& position, const Rotation& rotation) const
{
    (void)type;
    (void)position;
    (void)rotation;
    std::cerr << "TBIELA real crate\n!";
    return nullptr;
}
