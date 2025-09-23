#include "Menu.hpp"
#include <ControlWidget.hpp>
#include <Widget.hpp>
#include <memory>
#include <utility>

void Menu::addWidget(std::unique_ptr<Widget> widget)
{
    if (isControlWidget(widget.get()))
    {
        controlWidgets.push_back(std::move(widget));
    }
    else
    {
        staticWidgets.push_back(std::move(widget));
    }
}

bool Menu::isControlWidget(const Widget* widget)
{
    return !(dynamic_cast<const ControlWidget*>(widget) == nullptr);
}

void Menu::connect(ControlConnection& controlConnection)
{
    for (auto& widget : controlWidgets)
    {
        auto* widgetPtr { dynamic_cast<ControlWidget*>(widget.get()) };
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
    for (auto& widget : controlWidgets)
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
    for (auto& widget : controlWidgets)
    {
        widget->hide();
    }
}
