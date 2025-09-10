#pragma once

#include <Client.hpp>
#include <IMenuController.hpp>
#include <functional>
#include <memory>

using GuiExitCallback = std::function<void()>;

class MainApplication
{
public:
    MainApplication(
        std::unique_ptr<IMenuController> controller,
        std::unique_ptr<Client> client,
        GuiExitCallback callback
    );

    void handle(const MenuCommand& command);
    void handle(const GameCommand& command);

private:
    MenuConnection menuConnection;
    std::unique_ptr<IMenuController> menuController;
    GameConnection gameConnection;
    std::unique_ptr<Client> gameClient;
    GuiExitCallback guiExitCallback;

    void startSinglePlayerGame();
    void abortGame();
    void continueGame();
    void pauseGame();
};
