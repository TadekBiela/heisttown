#include "MainApplication.hpp"

MainApplication::MainApplication(
    std::unique_ptr<IMenuController> controller,
    std::unique_ptr<Client> client
)
    : menuController(std::move(controller))
    , gameClient(std::move(client))
{
    mainControlConnection = [&](const MainCommand& command)
    {
        this->control(command);
    };
    menuController->setMainControl(mainControlConnection);
    gameClient->setMainControl(mainControlConnection);
}

void MainApplication::control(const MainCommand& command)
{
    const auto menuCommandPart { command.substr(0, command.find("->")) };
    const auto actionCommandPart { command.substr(command.find("->"), command.size()) };

    if (menuCommandPart == "SinglePlayer")
    {
        if (actionCommandPart == "->Play")
        {
            gameClient->start();
        }
        else if (actionCommandPart == "->Pause")
        {
            menuController->control("Pause");
        }
    }
    else if (menuCommandPart == "Pause")
    {
        if (actionCommandPart == "->Abort")
        {
            gameClient->stop();
            menuController->showMenu();
        }
        else if (actionCommandPart == "->Continue")
        {
            gameClient->start();
        }
    }
}
