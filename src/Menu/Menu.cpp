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

auto Menu::isDynamicWidget(const WidgetType& type) -> bool
{
    return type == WidgetType::BUTTON;
}

void Menu::show()
{
    std::for_each(
        std::begin(staticWidgets),
        std::end(staticWidgets),
        [](std::unique_ptr<Widget>& widget)
        {
            widget->show();
        }
    );
    std::for_each(
        std::begin(dynamicWidgets),
        std::end(dynamicWidgets),
        [](std::unique_ptr<Widget>& widget)
        {
            widget->show();
        }
    );
}
