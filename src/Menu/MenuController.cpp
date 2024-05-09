#include "MenuController.hpp"
#include <iostream>

MenuController::MenuController(
    std::unique_ptr<IMenuParser> parser,
    std::unique_ptr<IFileLoader<TextFile>> source
)
{
    menus = parser->parse(std::move(source));
    hideAllMenus();
    connectMenus();
    initCurrentMenu();
}

void MenuController::hideAllMenus()
{
    for (auto& menuIt : menus)
    {
        auto& menu = menuIt.second;
        menu.hide();
    }
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
        hideAllMenus();
        currentMenu = menus.find("Pause");
        mainControlConnection(mainCommand);
        return;
    }

    hideAllMenus();
    currentMenu->second.show();
}

void MenuController::setMainControl(const MainControlConnection& controlConnection)
{
    mainControlConnection = controlConnection;
}
