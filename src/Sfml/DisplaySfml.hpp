#pragma once

#include "Drawable.hpp"
#include "EventHandler.hpp"
#include <Display.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

class DisplaySfml : public Display
{
public:
    DisplaySfml(unsigned int width, unsigned int height);

    void addDrawable(std::weak_ptr<Drawable> drawable);
    void addEventHandler(std::weak_ptr<EventHandler> handler);
    void display();
    void show() override;
    void hide() override;

private:
    sf::RenderWindow window;
    std::vector<std::weak_ptr<Drawable>> drawables;
    std::vector<std::weak_ptr<EventHandler>> handlers;

    void dispach();
    void render();
};
