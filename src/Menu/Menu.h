#ifndef MENU_H
#define MENU_H

#include <DynamicWidget.h>
#include <Widget.h>
#include <functional>
#include <memory>
#include <vector>

using DynamicWidgets = std::vector<std::unique_ptr<Widget>>;
using StaticWidgets = std::vector<std::unique_ptr<Widget>>;

class Menu
{
public:
    Menu() = default;
    virtual ~Menu() = default;
    Menu(Menu& menu) = delete;
    Menu(Menu&& menu) = default;
    Menu& operator=(Menu& menu) = delete;
    Menu& operator=(Menu&& menu) = default;

    void addWidget(std::unique_ptr<Widget> widget);
    void connect(ConnectionOutput& output);
    void show();
    void hide();

protected:
    DynamicWidgets dynamicWidgets {};
    StaticWidgets staticWidgets {};

private:
    static auto isDynamicWidget(const Widget* widget) -> bool;
};

#endif // MENU_H
