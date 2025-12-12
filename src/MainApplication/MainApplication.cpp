#include "MainApplication.hpp"
#include <IMenuController.hpp>
#include <LocalClient.hpp>
#include <LocalServer.hpp>
#include <memory>
#include <utility>

MainApplication::MainApplication(
    std::unique_ptr<IMenuController> controller,
    const std::shared_ptr<Scene>& scene,
    const std::shared_ptr<InputDispatcher>& inputDispatcher,
    GuiExitCallback callback,
    std::shared_ptr<Client> client,
    std::unique_ptr<Server> server
)
    : menuController(std::move(controller))
    , gameClient(std::move(client))
    , gameServer(std::move(server))
    , guiExitCallback(std::move(callback))
{
    menuConnection = [&](const MenuCommand& command)
    {
        this->handle(command);
    };
    menuController->connect(menuConnection);

    if (gameClient == nullptr)
    {
        gameClient = std::make_shared<LocalClient>(scene, inputDispatcher);
    }
    gameConnection = [&](const GameCommand& command)
    {
        this->handle(command);
    };
    gameClient->connect(gameConnection);

    if (gameServer == nullptr)
    {
        gameServer = std::make_unique<LocalServer>();
    }
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
