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
    command.size();
    menuController.get();
}
