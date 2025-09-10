#pragma once

#include <ControlWidget.hpp>
#include <Widget.hpp>
#include <memory>
#include <vector>

using ControlWidgets = std::vector<std::unique_ptr<Widget>>;
using StaticWidgets = std::vector<std::unique_ptr<Widget>>;

class Menu
{
public:
    Menu() = default;

    void addWidget(std::unique_ptr<Widget> widget);
    void connect(ControlConnection& controlConnection);
    void show();
    void hide();

protected:
    ControlWidgets controlWidgets;
    StaticWidgets staticWidgets;

private:
    static auto isControlWidget(const Widget* widget) -> bool;
};
