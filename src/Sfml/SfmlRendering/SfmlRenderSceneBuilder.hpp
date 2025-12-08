#pragma once

#include "SfmlRenderItem.hpp"
#include "SfmlTextureFile.hpp"
#include <FilesStorage.hpp>
#include <RenderItem.hpp>
#include <RenderSceneBuilder.hpp>
#include <SceneUpdate.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>

class SfmlRenderSceneBuilder : public RenderSceneBuilder
{
public:
    SfmlRenderSceneBuilder(
        sf::RenderWindow& inputWindow,
        std::shared_ptr<FilesStorage<SfmlTextureFile>> inputTextureStorage
    );

    void build(const SceneUpdate& sceneUpdate) override;
    [[nodiscard]] RenderItems popRenderItems() override;

protected:
    sf::Texture localMapTexture;
    RenderItems renderItems;

private:
    const SceneItemId mapId { 0 };
    SceneItemId itemIdCounter;
    sf::RenderWindow& window;
    std::shared_ptr<FilesStorage<SfmlTextureFile>> textureStorage;
    MapName loadedGlobalMapName;
    sf::Image globalMapImage;

    void loadGlobalMapIfNeeded(const MapName& mapName);
    void loadLocalMapTexture(const Position& playerGlobalPosition);
    [[nodiscard]] virtual std::unique_ptr<SfmlRenderItem> createItem(const SceneItemType& type, const Position& position, const Rotation& rotation);
    [[nodiscard]] const sf::Texture& getTexture(const SceneItemType& type) const;
    static std::string translateTypeToTextureName(const SceneItemType& type);
};
