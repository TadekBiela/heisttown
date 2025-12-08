#pragma once

#include "Drawable.hpp"
#include "EventHandler.hpp"
#include <RenderSceneBuilder.hpp>
#include <RenderTarget.hpp>
#include <SfmlRendering/SfmlTextureFile.hpp>
#include <FilesStorage.hpp>
#include <SceneItem.hpp>
#include <Scene.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

class DisplaySfml : public Scene
{
public:
    using Drawables = std::vector<std::shared_ptr<Drawable>>;
    using EventHandlers = std::vector<std::shared_ptr<EventHandler>>;

    DisplaySfml(
        unsigned int width,
        unsigned int height,
        std::unique_ptr<FilesStorage<SfmlTextureFile>> inputTextureStorage,
        std::unique_ptr<RenderSceneBuilder> inputSceneBuilder = nullptr,
        std::unique_ptr<RenderTarget> inputRenderTarget = nullptr
    );
    virtual ~DisplaySfml() override = default;

    virtual void addDrawable(std::shared_ptr<Drawable> drawable);
    virtual void addEventHandler(std::shared_ptr<EventHandler> handler);
    virtual void display();

    virtual void show() override;
    virtual void hide() override;
    virtual void update(const SceneUpdate& sceneUpdate) override;

protected:
    Drawables drawables;

private:
    sf::RenderWindow window;
    EventHandlers handlers;
    bool isSceneVisible;
    std::unique_ptr<FilesStorage<SfmlTextureFile>> textureStorage;
    std::unique_ptr<RenderSceneBuilder> sceneBuilder;
    std::unique_ptr<RenderTarget> renderTarget;

    void dispach();
    void render();
};
