#include "DisplaySfml.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <Sprite.hpp>

DisplaySfml::DisplaySfml(
    unsigned int width,
    unsigned int height
)
    : window(sf::VideoMode(width, height), "")
{
}

void DisplaySfml::addDrawable(std::shared_ptr<Drawable> drawable)
{
    drawables.push_back(std::move(drawable));
}

void DisplaySfml::addEventHandler(std::shared_ptr<EventHandler> handler)
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
        for (auto& handler : handlers)
        {
            const bool isHandled = handler->handle(event);
            if (isHandled)
            {
                break;
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

    for (auto& drawable : drawables)
    {
        drawable->draw(window);
    }

    window.display();
}

void DisplaySfml::update(const GameSceneUpdate& sceneUpdate)
{
    static bool isDrawed { false };

    if (isDrawed)
    {
        return;
    }

    for (const auto& gameObject : sceneUpdate.gameObjects)
    {
        auto sprite { std::make_shared<Sprite>(getTexture(gameObject.type), gameObject.position, gameObject.rotation) };
        addDrawable(sprite);
    }
    isDrawed = true;
}

sf::Texture& DisplaySfml::getTexture(const GoType& type)
{
    (void)type;
    static sf::Texture tex;

    if (tex.getSize().x == 0)
    {
        sf::Image img;
        img.create(50, 50, sf::Color::Red);
        tex.loadFromImage(img);
    }

    return tex;
}
