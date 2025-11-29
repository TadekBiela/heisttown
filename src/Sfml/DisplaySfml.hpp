#pragma once

#include "Drawable.hpp"
#include "EventHandler.hpp"
#include "SpriteFactory.hpp"
#include "TextureFile.hpp"
#include <FilesStorage.hpp>
#include <GameObject.hpp>
#include <GameScene.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include <memory>
#include <vector>

class DisplaySfml : public GameScene
{
public:
    using Drawables = std::vector<std::shared_ptr<Drawable>>;
    using EventHandlers = std::vector<std::shared_ptr<EventHandler>>;
    using Sprites = std::map<GoId, std::unique_ptr<Sprite>>;

    DisplaySfml(
        unsigned int width,
        unsigned int height,
        std::shared_ptr<FilesStorage<TextureFile>> inputTextureStorage,
        std::unique_ptr<SpriteFactory> inputSpriteFactory = nullptr
    );
    virtual ~DisplaySfml() override = default;

    virtual void addDrawable(std::shared_ptr<Drawable> drawable);
    virtual void addEventHandler(std::shared_ptr<EventHandler> handler);
    virtual void display();

    virtual void show() override;
    virtual void hide() override;
    virtual void update(const GameSceneUpdate& sceneUpdate) override;

protected:
    Drawables drawables;
    Sprites sprites;

private:
    sf::RenderWindow window;
    EventHandlers handlers;
    bool isGameSceneVisible;
    std::shared_ptr<FilesStorage<TextureFile>> textureStorage;
    std::unique_ptr<SpriteFactory> spriteFactory;
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
    // void updateSprite(const GameObject& spriteParamsUpdate);
    void addSprite(const GameObject& newSpriteParams);
};
