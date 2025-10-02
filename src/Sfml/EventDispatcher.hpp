#pragma once

#include "EventHandler.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

class EventDispatcher
{
public:
    ~EventDispatcher() = default;

    void addEventHandler(std::weak_ptr<EventHandler> handler);
    void dispatch(sf::RenderWindow& window);

private:
    std::vector<std::weak_ptr<EventHandler>> handlers;
};
