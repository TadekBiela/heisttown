#include "DisplaySfml.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/VideoMode.hpp>

DisplaySfml::DisplaySfml(
    unsigned int width,
    unsigned int height
)
    : window(sf::VideoMode(width, height), "")
{
}

void DisplaySfml::addDrawable(std::weak_ptr<Drawable> drawable)
{
    drawables.push_back(std::move(drawable));
}

void DisplaySfml::addEventHandler(std::weak_ptr<EventHandler> handler)
{
    handlers.push_back(std::move(handler));
}

void DisplaySfml::display()
{
    while (window.isOpen())
    {
        dispach();
        render();
    }
}

void DisplaySfml::dispach()
{
    sf::Event event {};
    while (window.pollEvent(event))
    {
        for (auto it = std::begin(handlers); it != std::end(handlers);)
        {
            if (auto handler = it->lock())
            {
                const bool isHandled = handler->handle(event);
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

        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void DisplaySfml::render()
{
    window.clear(sf::Color::Black);

    for (auto it = drawables.begin(); it != drawables.end();)
    {
        if (auto drawable = it->lock())
        {
            drawable->draw(window);
            ++it;
        }
        else
        {
            it = drawables.erase(it);
        }
    }

    window.display();
}
