#ifndef MAIN_APPLICATION_HPP
#define MAIN_APPLICATION_HPP

#include <IMenuController.hpp>
#include <memory>

class MainApplication
{
public:
    MainApplication(std::unique_ptr<IMenuController> menuController);
    virtual ~MainApplication() = default;

    void control(const MainCommand& command);

private:
    std::unique_ptr<IMenuController> menuController;
};

#endif // MAIN_APPLICATION_HPP
