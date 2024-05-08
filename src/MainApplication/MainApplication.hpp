#ifndef MAIN_APPLICATION_HPP
#define MAIN_APPLICATION_HPP

#include <Client.hpp>
#include <IMenuController.hpp>
#include <memory>

class MainApplication
{
public:
    MainApplication(
        std::unique_ptr<IMenuController> controller,
        std::unique_ptr<Client> client
    );
    virtual ~MainApplication() = default;

    void control(const MainCommand& command);

private:
    MainControlConnection mainControlConnection;
    std::unique_ptr<IMenuController> menuController;
    std::unique_ptr<Client> gameClient;
};

#endif // MAIN_APPLICATION_HPP
