#pragma once

#include <ControlWidget.hpp>
#include <Widget.hpp>
#include <functional>
#include <memory>
#include <vector>

using ControlWidgets = std::vector<std::unique_ptr<Widget>>;
using StaticWidgets = std::vector<std::unique_ptr<Widget>>;

class Menu
{
public:
    Menu() = default;
    virtual ~Menu() = default;
    Menu(const Menu& menu) = delete;
    Menu(Menu&& menu) = default;
    Menu& operator=(const Menu& menu) = delete;
    Menu& operator=(Menu&& menu) = default;

    void addWidget(std::unique_ptr<Widget> widget);
    void connect(ControlConnection& controlConnection);
    void show();
    void hide();

protected:
    ControlWidgets controlWidgets {};
    StaticWidgets staticWidgets {};

private:
    static auto isControlWidget(const Widget* widget) -> bool;
};
