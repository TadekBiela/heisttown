#ifndef IMENU_CONTROLLER_HPP
#define IMENU_CONTROLLER_HPP

#include <ControlWidget.hpp>
#include <MainControlConnector.hpp>

class IMenuController : public MainControlConnector
{
public:
    virtual ~IMenuController() = default;

    virtual void control(const WidgetCommand& command) = 0;
    virtual void showMenu() = 0;
};

#endif // IMENU_CONTROLLER_HPP
