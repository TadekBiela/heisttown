#include "DisplaySfml.hpp"
#include <FileLoader.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SfmlInput/SfmlInputSource.hpp>
#include <SfmlRendering/SfmlRenderSceneBuilder.hpp>
#include <SfmlRendering/SfmlRenderTarget.hpp>
#include <filesystem>

DisplaySfml::DisplaySfml(
    unsigned int width,
    unsigned int height,
    std::unique_ptr<FilesStorage<SfmlTextureFile>> inputTextureStorage,
    std::unique_ptr<RenderSceneBuilder> inputSceneBuilder,
    std::unique_ptr<RenderTarget> inputRenderTarget,
    std::shared_ptr<InputDispatcher> inputDispatcher
)
    : window(sf::VideoMode(width, height), "")
    , isSceneVisible(false)
    , textureStorage(std::move(inputTextureStorage))
    , sceneBuilder(std::move(inputSceneBuilder))
    , renderTarget(std::move(inputRenderTarget))
    , dispatcher(std::move(inputDispatcher))
{
    if (sceneBuilder == nullptr)
    {
        sceneBuilder = std::make_unique<SfmlRenderSceneBuilder>(window, std::move(textureStorage));
    }

    if (renderTarget == nullptr)
    {
        renderTarget = std::make_unique<SfmlRenderTarget>(window);
    }

    if (dispatcher == nullptr)
    {
        dispatcher = std::make_shared<InputDispatcher>(std::make_unique<SfmlInputSource>(window));
    }
}

void DisplaySfml::addDrawable(std::shared_ptr<Drawable> drawable)
{
    drawables.push_back(std::move(drawable));
}

std::shared_ptr<InputDispatcher> DisplaySfml::getDispatcher()
{
    return dispatcher;
}

void DisplaySfml::display()
{
    while (window.isOpen())
    {
        dispatcher->dispatch();
        render();
    }
}

void DisplaySfml::render()
{
    if (isSceneVisible)
    {
        renderTarget->render(sceneBuilder->popRenderItems());
    }
    else
    {
        window.clear(sf::Color::Black);

        for (auto& drawable : drawables)
        {
            drawable->draw(window);
        }
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
    sceneBuilder->build(sceneUpdate);
}
