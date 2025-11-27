#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>

class TextureFile
{
public:
    TextureFile() = default;
    explicit TextureFile(const std::string& filePath);

    const sf::Texture& getTexture() const;

private:
    sf::Texture texture;
};
