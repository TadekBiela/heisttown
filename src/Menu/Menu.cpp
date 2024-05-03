#include "Menu.h"
#include <typeinfo>

void Menu::addWidget(std::unique_ptr<Widget> widget)
{
    if (isDynamicWidget(widget.get()))
    {
        dynamicWidgets.push_back(std::move(widget));
    }
    else
    {
        staticWidgets.push_back(std::move(widget));
    }
}

auto Menu::isDynamicWidget(const Widget* widget) -> bool
{
    return !(dynamic_cast<const DynamicWidget*>(widget) == nullptr);
}

void Menu::connect(ControlConnection& controlConnection)
{
    for (auto& widget : dynamicWidgets)
    {
        auto* widgetPtr { dynamic_cast<DynamicWidget*>(widget.get()) };
        if (widgetPtr != nullptr)
        {
            widgetPtr->connect(controlConnection);
        }
    }
}

void Menu::show()
{
    for (auto& widget : staticWidgets)
    {
        widget->show();
    }
    for (auto& widget : dynamicWidgets)
    {
        widget->show();
    }
}

void Menu::hide()
{
    for (auto& widget : staticWidgets)
    {
        widget->hide();
    }
    for (auto& widget : dynamicWidgets)
    {
        widget->hide();
    }
}
