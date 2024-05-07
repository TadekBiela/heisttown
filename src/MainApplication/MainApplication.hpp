#ifndef MAIN_APPLICATION_HPP
#define MAIN_APPLICATION_HPP

#include <IMenuController.hpp>
#include <memory>

class MainApplication
{
public:
    MainApplication(std::unique_ptr<IMenuController> controller);
    virtual ~MainApplication() = default;

    void control(const MainCommand& command);

private:
    MainControlConnection mainControlConnection;
    std::unique_ptr<IMenuController> menuController;
};

#endif // MAIN_APPLICATION_HPP
