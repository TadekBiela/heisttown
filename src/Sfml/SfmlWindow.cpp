#include "SfmlWindow.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SfmlInput/SfmlInputSource.hpp>
#include <SfmlRendering/SfmlRenderSceneBuilder.hpp>
#include <SfmlRendering/SfmlRenderTarget.hpp>

SfmlWindow::SfmlWindow(
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

void SfmlWindow::add(std::shared_ptr<RenderItem> item)
{
    renderItems.push_back(std::move(item));
}

sf::RenderTarget& SfmlWindow::getRenderTarget()
{
    return window;
}

std::shared_ptr<InputDispatcher> SfmlWindow::getDispatcher()
{
    return dispatcher;
}

void SfmlWindow::display()
{
    while (window.isOpen())
    {
        dispatcher->dispatch();
        render();
    }
}

void SfmlWindow::render()
{
    if (isSceneVisible)
    {
        renderTarget->render(sceneBuilder->popRenderItems());
    }
    else
    {
        window.clear(sf::Color::Black);

        renderTarget->render(renderItems);
    }

    window.display();
}

void SfmlWindow::show()
{
    isSceneVisible = true;
}

void SfmlWindow::hide()
{
    isSceneVisible = false;
}

void SfmlWindow::update(const SceneUpdate& sceneUpdate)
{
    sceneBuilder->build(sceneUpdate);
}
