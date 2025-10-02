#include "Renderer.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/VideoMode.hpp>

Renderer::Renderer(
    unsigned int width,
    unsigned int height
)
    : window(sf::VideoMode(width, height), "")
{
}

void Renderer::addDrawable(std::weak_ptr<Drawable> drawable)
{
    drawables.push_back(std::move(drawable));
}

void Renderer::render()
{
    while (window.isOpen())
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
}

sf::RenderWindow& Renderer::getWindow()
{
    return window;
}
