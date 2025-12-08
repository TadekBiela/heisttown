#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>

class SfmlTextureFile
{
public:
    SfmlTextureFile() = default;
    explicit SfmlTextureFile(const std::string& filePath);

    const sf::Texture& getTexture() const;

private:
    sf::Texture texture;
};
