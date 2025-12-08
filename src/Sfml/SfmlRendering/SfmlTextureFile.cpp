#include "SfmlTextureFile.hpp"

SfmlTextureFile::SfmlTextureFile(const std::string& filePath)
{
    texture.loadFromFile(filePath);
}

const sf::Texture& SfmlTextureFile::getTexture() const
{
    return texture;
}
