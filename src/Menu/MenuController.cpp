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
    for (auto& menuIt : menus)
    {
        auto& menu = menuIt.second;
        menu.connect(output);
    }
}

void MenuController::control(const WidgetMessage& message)
{
    if (auto menu = menus.find(message); menu != std::end(menus))
    {
        previousMenu = currentMenu;
        currentMenu = menu;
    }
    else if (message == "Back")
    {
        std::swap(currentMenu, previousMenu);
    }
    else
    {
        std::cerr << "MenuController::control - unknown command: " << message << std::endl;
    }

    hideAllMenus();
    currentMenu->second.show();
}

void MenuController::initCurrentMenu()
{
    if (currentMenu = menus.find("MainMenu"); currentMenu != std::end(menus))
    {
        previousMenu = currentMenu;
        currentMenu->second.show();
    }
    else
    {
        std::cerr << "MenuController::initCurrentMenu - missing MainMenu! Control on menus disabled.\n";
    }
}

void MenuController::hideAllMenus()
{
    for (auto& menuIt : menus)
    {
        auto& menu = menuIt.second;
        menu.hide();
    }
}
