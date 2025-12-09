#pragma once

#include <Client.hpp>
#include <Scene.hpp>
#include <IMenuController.hpp>
#include <Server.hpp>
#include <functional>
#include <memory>

using GuiExitCallback = std::function<void()>;

class MainApplication
{
public:
    MainApplication(
        std::unique_ptr<IMenuController> controller,
        const std::shared_ptr<Scene>& scene,
        std::unique_ptr<Input> input,
        GuiExitCallback callback,
        std::shared_ptr<Client> client = nullptr,
        std::unique_ptr<Server> server = nullptr
    );

    void handle(const MenuCommand& command);
    void handle(const GameCommand& command);
    void run();

private:
    MenuConnection menuConnection;
    std::unique_ptr<IMenuController> menuController;
    GameConnection gameConnection;
    std::shared_ptr<Client> gameClient;
    std::unique_ptr<Server> gameServer;
    GuiExitCallback guiExitCallback;

    void startSinglePlayerGame();
    void abortGame();
    void continueGame();
    void pauseGame();
};
