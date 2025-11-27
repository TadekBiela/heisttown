#include "TextureFile.hpp"

TextureFile::TextureFile(const std::string& filePath)
{
    texture.loadFromFile(filePath);
}

const sf::Texture& TextureFile::getTexture() const
{
    return texture;
}
