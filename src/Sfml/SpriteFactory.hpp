#pragma once

#include "Sprite.hpp"
#include "TextureFile.hpp"
#include <FilesStorage.hpp>
#include <GameObject.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

class SpriteFactory
{
public:
    explicit SpriteFactory(std::shared_ptr<FilesStorage<TextureFile>> inputTextureStorage);
    virtual ~SpriteFactory() = default;

    [[nodiscard]] virtual std::unique_ptr<Sprite> create(const GoType& type, const Position& position, const Rotation& rotation);

private:
    GoId goIdCounter;
    std::shared_ptr<FilesStorage<TextureFile>> textureStorage;

    [[nodiscard]] const sf::Texture& getTexture(const GoType& type) const;
    static std::string translateTypeToTextureName(const GoType& type);
};
