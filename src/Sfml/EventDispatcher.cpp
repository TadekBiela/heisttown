#include "EventDispatcher.hpp"
#include "EventHandler.hpp"
#include <SFML/Window/Event.hpp>

void EventDispatcher::addEventHandler(std::weak_ptr<EventHandler> handler)
{
    handlers.push_back(std::move(handler));
}

void EventDispatcher::dispatch(sf::RenderWindow& window)
{
    sf::Event event {};
    while (window.isOpen())
    {
        if (not window.pollEvent(event))
        {
            continue;
        }

        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        for (auto it = std::begin(handlers); it != std::end(handlers);)
        {
            if (auto handler = it->lock())
            {
                const bool isHandled { handler->handle(event) };
                if (isHandled)
                {
                    break;
                }
                ++it;
            }
            else
            {
                it = handlers.erase(it);
            }
        }
    }
}
