#pragma once

#include <Client.hpp>
#include <MainControlConnector.hpp>
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
    virtual ~MainApplication() = default;

    void control(const MainCommand& command);

private:
    MainControlConnection mainControlConnection;
    std::unique_ptr<IMenuController> menuController;
    std::unique_ptr<Client> gameClient;
    GuiExitCallback guiExitCallback;
};
