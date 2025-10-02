#pragma once

#include <WidgetControl.hpp>
#include <Widget.hpp>
#include <memory>
#include <vector>

using ControlWidgets = std::vector<std::shared_ptr<Widget>>;
using StaticWidgets = std::vector<std::shared_ptr<Widget>>;

class Menu
{
public:
    Menu() = default;

    void addWidget(std::shared_ptr<Widget> widget);
    void connect(ControlConnection& controlConnection);
    void show();
    void hide();

protected:
    ControlWidgets controlWidgets;
    StaticWidgets staticWidgets;

private:
    static bool isWidgetWithControl(const Widget* widget);
};
