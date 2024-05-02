#include "MenuController.h"
#include <iostream>

MenuController::MenuController(
    std::unique_ptr<IMenuParser> parser,
    std::unique_ptr<IFileLoader<TextFile>> source
)
{
    menus = parser->parse(std::move(source));
    connectMenus();
    initCurrentMenu();
}

void MenuController::connectMenus()
{
    ConnectionOutput output = [&](const WidgetMessage& message)
    {
        this->control(message);
    };
    for (auto& menu : menus)
    {
        menu.connect(output);
    }
}

void MenuController::control(const WidgetMessage& message)
{
    std::cout << "MenuController::control - message: " << message
              << " - all menus: " << menus.size() << std::endl;
}

void MenuController::initCurrentMenu()
{
    currentMenu = std::begin(menus);
    previousMenu = currentMenu;

    if (currentMenu != std::end(menus))
    {
        currentMenu->show();
    }
}

void MenuController::hideAllMenus()
{
    for (auto& menu : menus)
    {
        menu.hide();
    }
}
