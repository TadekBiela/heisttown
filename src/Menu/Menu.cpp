#include "Menu.h"
#include <algorithm>

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

void Menu::connect(ConnectionOutput& output)
{
    output("");
    dynamicWidgets.size(); // temporary for Clang Tidy
}

auto Menu::isDynamicWidget(const WidgetType& type) -> bool
{
    return type == WidgetType::BUTTON;
}

void Menu::show()
{
    runOnAllWidgets(
        [](std::unique_ptr<Widget>& widget)
        {
            widget->show();
        }
    );
}

void Menu::hide()
{
    runOnAllWidgets(
        [](std::unique_ptr<Widget>& widget)
        {
            widget->hide();
        }
    );
}

void Menu::runOnAllWidgets(const std::function<void(std::unique_ptr<Widget>&)>& widgetMethod)
{
    std::for_each(
        std::begin(staticWidgets),
        std::end(staticWidgets),
        widgetMethod
    );
    std::for_each(
        std::begin(dynamicWidgets),
        std::end(dynamicWidgets),
        widgetMethod
    );
}
