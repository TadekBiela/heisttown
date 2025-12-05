#include "DisplaySfml.hpp"
#include "Sprite.hpp"
#include <FileLoader.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <filesystem>

DisplaySfml::DisplaySfml(
    unsigned int width,
    unsigned int height,
    std::shared_ptr<FilesStorage<TextureFile>> inputTextureStorage,
    std::unique_ptr<SpriteFactory> inputSpriteFactory
)
    : window(sf::VideoMode(width, height), "")
    , isSceneVisible(false)
    , textureStorage(std::move(inputTextureStorage))
    , spriteFactory(std::move(inputSpriteFactory))
    , playerPosition()
    , playerRotation(0.0F)
{
    if (spriteFactory == nullptr)
    {
        spriteFactory = std::make_unique<SpriteFactory>(textureStorage);
    }

    localMapTexture.create(width, height);
    playerPosition.x = static_cast<float>(width) / 2.0F;
    playerPosition.y = static_cast<float>(height) / 2.0F;
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

    if (isSceneVisible)
    {
        renderLocalMap();

        for (auto& sprite : sprites)
        {
            sprite.second->draw(window);
        }

        renderPlayer();
    }

    window.display();
}

void DisplaySfml::show()
{
    isSceneVisible = true;
}

void DisplaySfml::hide()
{
    isSceneVisible = false;
}

void DisplaySfml::update(const SceneUpdate& sceneUpdate)
{
    loadGlobalMapIfNeeded(sceneUpdate.mapName);
    loadLocalMap(sceneUpdate.playerGlobalPosition);

    for (const auto& gameObject : sceneUpdate.sceneItems)
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

void DisplaySfml::loadGlobalMapIfNeeded(const MapName& mapName)
{
    const sf::Vector2u emptyImage { 0, 0 };
    if (globalMapImage.getSize() == emptyImage)
    {
        const auto& textureFile { textureStorage->getFile(mapName) };
        globalMapImage = textureFile.getTexture().copyToImage();
    }
}

void DisplaySfml::loadLocalMap(const Position& playerGlobalPosition)
{
    const auto& displaySize { window.getSize() };

    const sf::IntRect localMapTextureRect(
        static_cast<int>(playerGlobalPosition.x) - static_cast<int>(displaySize.x),
        static_cast<int>(playerGlobalPosition.y) - static_cast<int>(displaySize.y),
        static_cast<int>(displaySize.x),
        static_cast<int>(displaySize.y)
    );

    sf::Image localMapImage;
    localMapImage.create(displaySize.x, displaySize.y);
    localMapImage.copy(globalMapImage, 0, 0, localMapTextureRect, false);

    localMapTexture.loadFromImage(localMapImage);
    localMap.setTexture(localMapTexture);
}

void DisplaySfml::renderLocalMap()
{
    window.draw(localMap);
}

void DisplaySfml::renderPlayer()
{
    auto playerSprite { spriteFactory->create(SceneItemType::PLAYER, playerPosition, playerRotation) };
    playerSprite->draw(window);
}

// void DisplaySfml::updateSprite(const SceneItem& spriteParamsUpdate)
// {
//     (void)spriteParamsUpdate;
// }

void DisplaySfml::addSprite(const SceneItem& newSpriteParams)
{
    auto sprite { spriteFactory->create(newSpriteParams.type, newSpriteParams.position, newSpriteParams.rotation) };
    sprites[sprite->getId()] = std::move(sprite);
}
