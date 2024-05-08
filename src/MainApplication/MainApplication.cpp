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
}

void MainApplication::control(const MainCommand& command)
{
    if (command.find("SinglePlayer") != MainCommand::npos)
    {
        if (command.find("->Play") != MainCommand::npos)
        {
            gameClient->startSinglePlayerGame();
        }
    }
}
