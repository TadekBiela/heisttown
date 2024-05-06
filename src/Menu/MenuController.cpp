#include "MenuController.hpp"
#include <iostream>

MenuController::MenuController(
    std::unique_ptr<IMenuParser> parser,
    std::unique_ptr<IFileLoader<TextFile>> source,
    const MainControlConnection& mainControlConnection
)
    : mainControlConnection(mainControlConnection)
{
    menus = parser->parse(std::move(source));
    hideAllMenus();
    connectMenus();
    initCurrentMenu();
}

void MenuController::connectMenus()
{
    controlConnection = [&](const WidgetCommand& command)
    {
        this->control(command);
    };
    for (auto& menuIt : menus)
    {
        auto& menu = menuIt.second;
        menu.connect(controlConnection);
    }
}

void MenuController::control(const WidgetCommand& command)
{
    if (auto menu = menus.find(command); menu != std::end(menus))
    {
        previousMenu = currentMenu;
        currentMenu = menu;
    }
    else if (command == "Back")
    {
        std::swap(currentMenu, previousMenu);
    }
    else
    {
        MainCommand mainCommand { currentMenu->first + "->" + command };
        mainControlConnection(mainCommand);
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
