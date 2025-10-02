#pragma once

#include <ControlWidget.hpp>
#include <functional>

enum class MenuCommand : char
{
    StartSinglePlayer = 0,
    PauseSinglePlayer = 1,
    Abort = 2,
    Continue = 3,
    Exit = 4,
    NoCommand = 5
};

using MenuConnection = std::function<void(const MenuCommand&)>;


class IMenuController
{
public:
    virtual ~IMenuController() = default;

    virtual void handle(const WidgetCommand& command) = 0;
    virtual void connect(const MenuConnection& connection) = 0;
    virtual void showMenu() = 0;
};
