#ifndef MENU_H
#define MENU_H

#include <Widget.h>
#include <memory>
#include <vector>

using DynamicWidgets = std::vector<std::unique_ptr<Widget>>;
using StaticWidgets = std::vector<std::unique_ptr<Widget>>;

class Menu
{
public:
    Menu() = default;
    virtual ~Menu() = default;

    void addWidget(std::unique_ptr<Widget> widget);

protected:
    DynamicWidgets dynamicWidgets {};
    StaticWidgets staticWidgets {};

private:
    static auto isDynamicWidget(const WidgetType& type) -> bool;
};

#endif // MENU_H
