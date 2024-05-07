#include "MainApplication.hpp"

MainApplication::MainApplication(std::unique_ptr<IMenuController> controller)
    : menuController(std::move(controller))
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
