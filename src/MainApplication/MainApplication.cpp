#include "MainApplication.hpp"
#include <Client.hpp>
#include <IMenuController.hpp>
#include <LocalServer.hpp>
#include <memory>
#include <utility>

MainApplication::MainApplication(
    std::unique_ptr<IMenuController> controller,
    std::shared_ptr<Client> client,
    GuiExitCallback callback
)
    : menuController(std::move(controller))
    , gameClient(std::move(client))
    , gameServer(std::make_unique<LocalServer>())
    , guiExitCallback(std::move(callback))
{
    menuConnection = [&](const MenuCommand& command)
    {
        this->handle(command);
    };
    menuController->connect(menuConnection);

    gameConnection = [&](const GameCommand& command)
    {
        this->handle(command);
    };
    gameClient->connect(gameConnection);
}

void MainApplication::handle(const MenuCommand& command)
{
    switch (command)
    {
        case MenuCommand::StartSinglePlayer:
            startSinglePlayerGame();
            return;
        case MenuCommand::Abort:
            abortGame();
            return;
        case MenuCommand::Continue:
            continueGame();
            return;
        case MenuCommand::Exit:
            guiExitCallback();
        default:
            return;
    }
}

void MainApplication::startSinglePlayerGame()
{
    gameClient->start();
    gameServer->connect(gameClient);
    gameServer->start();
}

void MainApplication::abortGame()
{
    gameClient->stop();
    menuController->showMenu();
}

void MainApplication::continueGame()
{
    gameClient->start();
}

void MainApplication::handle(const GameCommand& command)
{
    switch (command)
    {
        case GameCommand::Pause:
            pauseGame();
            return;
        default:
            return;
    }
}

void MainApplication::pauseGame()
{
    gameClient->stop();
    menuController->handle("Pause");
}

void MainApplication::run()
{
    menuController->showMenu();
}
