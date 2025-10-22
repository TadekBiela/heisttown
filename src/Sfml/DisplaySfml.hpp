#pragma once

#include "Drawable.hpp"
#include "EventHandler.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

class DisplaySfml
{
public:
    DisplaySfml(unsigned int width, unsigned int height);

    void addDrawable(std::weak_ptr<Drawable> drawable);
    void addEventHandler(std::weak_ptr<EventHandler> handler);
    void display();

private:
    sf::RenderWindow window;
    std::vector<std::weak_ptr<Drawable>> drawables;
    std::vector<std::weak_ptr<EventHandler>> handlers;

    void dispach();
    void render();
};
