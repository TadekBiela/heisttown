#include "Menu.h"

void Menu::addWidget(std::unique_ptr<Widget> widget)
{
    if (isDynamicWidget(widget->type()))
    {
        dynamicWidgets.push_back(std::move(widget));
    }
    else
    {
        staticWidgets.push_back(std::move(widget));
    }
}

auto Menu::isDynamicWidget(const WidgetType& type) -> bool
{
    return type == WidgetType::BUTTON;
}
