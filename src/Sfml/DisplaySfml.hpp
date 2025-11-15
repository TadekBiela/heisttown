#pragma once

#include "Drawable.hpp"
#include "EventHandler.hpp"
#include <GameScene.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

class DisplaySfml : public GameScene
{
public:
    using Drawables = std::vector<std::shared_ptr<Drawable>>;
    using EventHandlers = std::vector<std::shared_ptr<EventHandler>>;

    DisplaySfml(unsigned int width, unsigned int height);

    void addDrawable(std::shared_ptr<Drawable> drawable);
    void addEventHandler(std::shared_ptr<EventHandler> handler);
    void display();
    void update(const GameSceneUpdate& sceneUpdate) override;

protected:
    Drawables drawables;

private:
    sf::RenderWindow window;
    EventHandlers handlers;

    void dispach();
    void render();
    static sf::Texture& getTexture(const GoType& type);
};
