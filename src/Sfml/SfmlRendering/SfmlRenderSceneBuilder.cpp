#include "SfmlRenderSceneBuilder.hpp"
#include <iostream>

SfmlRenderSceneBuilder::SfmlRenderSceneBuilder(
    sf::RenderWindow& inputWindow,
    std::shared_ptr<FilesStorage<SfmlTextureFile>> inputTextureStorage
)
    : itemIdCounter(1)
    , window(inputWindow)
    , textureStorage(std::move(inputTextureStorage))
{
    const auto localMapSize = window.getSize();
    localMapTexture.create(localMapSize.x, localMapSize.y);
}

void SfmlRenderSceneBuilder::build(const SceneUpdate& sceneUpdate)
{
    if (sceneUpdate.mapName.empty())
    {
        std::cerr << __func__ << " mapName is empty!\n";
        return;
    }

    loadGlobalMapIfNeeded(sceneUpdate.mapName);
    loadLocalMapTexture(sceneUpdate.playerGlobalPosition);

    renderItems.push_back(std::make_unique<SfmlRenderItem>(window, mapId, localMapTexture, Position { 0.0F, 0.0F }, 0.0F));

    for (const auto& sceneItem : sceneUpdate.sceneItems)
    {
        auto renderItem { createItem(sceneItem.type, sceneItem.position, sceneItem.rotation) };
        renderItems.push_back(std::move(renderItem));
    }

    const Position playerLocalPosition {
        static_cast<float>(window.getSize().x) / 2.0F,
        static_cast<float>(window.getSize().y) / 2.0F
    };
    auto playerRenderItem { createItem(SceneItemType::PLAYER, playerLocalPosition, sceneUpdate.playerRotation) };
    renderItems.push_back(std::move(playerRenderItem));
}

void SfmlRenderSceneBuilder::loadGlobalMapIfNeeded(const MapName& mapName)
{
    if (loadedGlobalMapName != mapName)
    {
        const auto& textureFile { textureStorage->getFile(mapName) };
        globalMapImage = textureFile.getTexture().copyToImage();
        loadedGlobalMapName = mapName;
    }
}

void SfmlRenderSceneBuilder::loadLocalMapTexture(const Position& playerGlobalPosition)
{
    if (globalMapImage.getSize().x == 0)
    {
        std::cerr << __func__ << " globalMapImage is empty!\n";
        return;
    }

    const auto& displaySize { window.getSize() };

    sf::IntRect localMapTextureRect(
        static_cast<int>(playerGlobalPosition.x) - static_cast<int>(displaySize.x / 2),
        static_cast<int>(playerGlobalPosition.y) - static_cast<int>(displaySize.y / 2),
        static_cast<int>(displaySize.x),
        static_cast<int>(displaySize.y)
    );

    localMapTextureRect.left = std::clamp(
        localMapTextureRect.left,
        0,
        static_cast<int>(globalMapImage.getSize().x) - localMapTextureRect.width
    );

    localMapTextureRect.top = std::clamp(
        localMapTextureRect.top,
        0,
        static_cast<int>(globalMapImage.getSize().y) - localMapTextureRect.height
    );

    sf::Image localMapImage;
    localMapImage.create(displaySize.x, displaySize.y);
    localMapImage.copy(globalMapImage, 0, 0, localMapTextureRect, false);

    localMapTexture.update(localMapImage);
}

std::unique_ptr<SfmlRenderItem> SfmlRenderSceneBuilder::createItem(const SceneItemType& type, const Position& position, const Rotation& rotation)
{
    const auto& texture { getTexture(type) };
    const Position textureOffset {
        static_cast<float>(texture.getSize().x / 2),
        static_cast<float>(texture.getSize().y / 2)
    };
    const Position itemPosition {
        position.x - textureOffset.x,
        position.y - textureOffset.y
    };
    return std::make_unique<SfmlRenderItem>(window, itemIdCounter++, texture, itemPosition, rotation);
}

const sf::Texture& SfmlRenderSceneBuilder::getTexture(const SceneItemType& type) const
{
    return textureStorage->getFile(translateTypeToTextureName(type)).getTexture();
}

std::string SfmlRenderSceneBuilder::translateTypeToTextureName(const SceneItemType& type)
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

RenderItems SfmlRenderSceneBuilder::popRenderItems()
{
    RenderItems items = std::move(renderItems);
    renderItems.clear();
    itemIdCounter = 1;
    return items;
}
