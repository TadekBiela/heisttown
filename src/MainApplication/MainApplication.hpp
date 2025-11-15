#pragma once

#include <Client.hpp>
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
        std::shared_ptr<Client> client,
        GuiExitCallback callback
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
