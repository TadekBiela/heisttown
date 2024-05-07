#ifndef IMENU_CONTROLLER_HPP
#define IMENU_CONTROLLER_HPP

#include <ControlWidget.hpp>

using MainCommand = std::string;
using MainControlConnection = std::function<void(const MainCommand&)>;

class IMenuController
{
public:
    virtual ~IMenuController() = default;

    virtual void control(const WidgetCommand& command) = 0;
    virtual void setMainControl(const MainControlConnection& mainControlConnection) = 0;
};

#endif // IMENU_CONTROLLER_HPP
