#pragma once

#include <InputDispatcher.hpp>
#include <RenderSceneBuilder.hpp>
#include <RenderTarget.hpp>
#include <SfmlRendering/SfmlTextureFile.hpp>
#include <FilesStorage.hpp>
#include <SceneItem.hpp>
#include <Scene.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class SfmlWindow : public Scene
{
public:
    SfmlWindow(
        unsigned int width,
        unsigned int height,
        std::unique_ptr<FilesStorage<SfmlTextureFile>> inputTextureStorage,
        std::unique_ptr<RenderSceneBuilder> inputSceneBuilder = nullptr,
        std::unique_ptr<RenderTarget> inputRenderTarget = nullptr,
        const std::shared_ptr<InputDispatcher>& inputDispatcher = nullptr
    );
    virtual ~SfmlWindow() override = default;

    virtual void add(std::shared_ptr<RenderItem> item);
    virtual sf::RenderTarget& getRenderTarget();
    virtual std::shared_ptr<InputDispatcher> getDispatcher();
    virtual void display();
    virtual void show() override;
    virtual void hide() override;
    virtual void update(const SceneUpdate& sceneUpdate) override;

protected:
    RenderItems renderItems;

private:
    sf::RenderWindow window;
    bool isSceneVisible;
    std::unique_ptr<FilesStorage<SfmlTextureFile>> textureStorage;
    std::unique_ptr<RenderSceneBuilder> sceneBuilder;
    std::unique_ptr<RenderTarget> renderTarget;
    std::shared_ptr<InputDispatcher> dispatcher;

    void render();
};
