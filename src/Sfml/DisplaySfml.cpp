#include "DisplaySfml.hpp"
#include <FileLoader.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <Sprite.hpp>
#include <filesystem>

DisplaySfml::DisplaySfml(unsigned int width, unsigned int height, std::unique_ptr<SpriteFactory> inputSpriteFactory)
    : window(sf::VideoMode(width, height), "")
    , spriteFactory(std::move(inputSpriteFactory))
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
    for (auto& sprite : sprites)
    {
        sprite.second->draw(window);
    }

    window.display();
}

void DisplaySfml::update(const GameSceneUpdate& sceneUpdate)
{
    for (const auto& gameObject : sceneUpdate.gameObjects)
    {
        if (sprites.find(gameObject.id) != sprites.end())
        {
            // updateSprite(gameObject);
        }
        else
        {
            addSprite(gameObject);
        }
    }
}

// void DisplaySfml::updateSprite(const GameObject& spriteParamsUpdate)
// {
//     (void)spriteParamsUpdate;
// }

void DisplaySfml::addSprite(const GameObject& newSpriteParams)
{
    auto sprite { spriteFactory->create(newSpriteParams.type, newSpriteParams.position, newSpriteParams.rotation) };
    sprites[sprite->getId()] = std::move(sprite);
}
