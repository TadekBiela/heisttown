#pragma once

#include <SFML/Window/Event.hpp>

class EventHandler
{
public:
    virtual ~EventHandler() = default;

    [[nodiscard]] virtual bool handle(const sf::Event& event) const = 0;
};
