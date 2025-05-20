#pragma once

#include <ControlWidget.hpp>
#include <MainControlConnector.hpp>

class IMenuController : public MainControlConnector
{
public:
    virtual ~IMenuController() = default;

    virtual void control(const WidgetCommand& command) = 0;
    virtual void showMenu() = 0;
};
