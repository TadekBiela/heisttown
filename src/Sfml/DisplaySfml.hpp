#pragma once

#include "Drawable.hpp"
#include "EventHandler.hpp"
#include <SfmlRendering/SfmlRenderItem.hpp>
#include <SfmlRendering/SfmlRenderItemFactory.hpp>
#include "TextureFile.hpp"
#include <FilesStorage.hpp>
#include <SceneItem.hpp>
#include <Scene.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include <memory>
#include <vector>

class DisplaySfml : public Scene
{
public:
    using Drawables = std::vector<std::shared_ptr<Drawable>>;
    using EventHandlers = std::vector<std::shared_ptr<EventHandler>>;
    using SfmlRenderItems = std::map<SceneItemId, std::unique_ptr<SfmlRenderItem>>;

    DisplaySfml(
        unsigned int width,
        unsigned int height,
        std::shared_ptr<FilesStorage<TextureFile>> inputTextureStorage,
        std::unique_ptr<SfmlRenderItemFactory> inputRenderItemFactory = nullptr
    );
    virtual ~DisplaySfml() override = default;

    virtual void addDrawable(std::shared_ptr<Drawable> drawable);
    virtual void addEventHandler(std::shared_ptr<EventHandler> handler);
    virtual void display();

    virtual void show() override;
    virtual void hide() override;
    virtual void update(const SceneUpdate& sceneUpdate) override;

protected:
    Drawables drawables;
    SfmlRenderItems renderItems;

private:
    sf::RenderWindow window;
    EventHandlers handlers;
    bool isSceneVisible;
    std::shared_ptr<FilesStorage<TextureFile>> textureStorage;
    std::unique_ptr<SfmlRenderItemFactory> renderItemFactory;
    sf::Image globalMapImage;
    sf::Texture localMapTexture;
    sf::Sprite localMap;
    Position playerPosition;
    Rotation playerRotation;

    void dispach();
    void render();
    void loadGlobalMapIfNeeded(const MapName& mapName);
    void loadLocalMap(const Position& playerGlobalPosition);
    void renderLocalMap();
    void renderPlayer();
    void addRenderItem(const SceneItem& sceneItem);
};
