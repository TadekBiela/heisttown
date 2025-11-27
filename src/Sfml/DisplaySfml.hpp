#pragma once

#include "Drawable.hpp"
#include "EventHandler.hpp"
#include "SpriteFactory.hpp"
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

    DisplaySfml(unsigned int width, unsigned int height, std::unique_ptr<SpriteFactory> inputSpriteFactory);
    virtual ~DisplaySfml() = default;

    virtual void addDrawable(std::shared_ptr<Drawable> drawable);
    virtual void addEventHandler(std::shared_ptr<EventHandler> handler);
    virtual void display();
    virtual void update(const GameSceneUpdate& sceneUpdate) override;

protected:
    Drawables drawables;
    Sprites sprites;

private:
    sf::RenderWindow window;
    EventHandlers handlers;
    std::unique_ptr<SpriteFactory> spriteFactory;

    void dispach();
    void render();
    // void updateSprite(const GameObject& spriteParamsUpdate);
    void addSprite(const GameObject& newSpriteParams);
};
