#pragma once

#include "Drawable.hpp"
#include <InputDispatcher.hpp>
#include <InputHandler.hpp>
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

    DisplaySfml(
        unsigned int width,
        unsigned int height,
        std::unique_ptr<FilesStorage<SfmlTextureFile>> inputTextureStorage,
        std::unique_ptr<RenderSceneBuilder> inputSceneBuilder = nullptr,
        std::unique_ptr<RenderTarget> inputRenderTarget = nullptr,
        std::shared_ptr<InputDispatcher> inputDispatcher = nullptr
    );
    virtual ~DisplaySfml() override = default;

    virtual void addDrawable(std::shared_ptr<Drawable> drawable);
    virtual std::shared_ptr<InputDispatcher> getDispatcher();
    virtual void display();

    virtual void show() override;
    virtual void hide() override;
    virtual void update(const SceneUpdate& sceneUpdate) override;

protected:
    Drawables drawables;

private:
    sf::RenderWindow window;
    bool isSceneVisible;
    std::unique_ptr<FilesStorage<SfmlTextureFile>> textureStorage;
    std::unique_ptr<RenderSceneBuilder> sceneBuilder;
    std::unique_ptr<RenderTarget> renderTarget;
    std::shared_ptr<InputDispatcher> dispatcher;

    void render();
};
