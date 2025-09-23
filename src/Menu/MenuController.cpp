#include "MenuController.hpp"
#include "IMenuController.hpp"
#include "IMenuParser.hpp"
#include <ControlWidget.hpp>
#include <IFileLoader.hpp>
#include <TextFile.hpp>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>

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
        this->handle(command);
    };
    for (auto& menuIt : menus)
    {
        auto& menu = menuIt.second;
        menu.connect(controlConnection);
    }
}

void MenuController::initCurrentMenu()
{
    if (auto mainMenu = menus.find("MainMenu"); mainMenu != std::end(menus))
    {
        currentMenuStack.push(mainMenu);
        showCurrentMenu();
    }
    else
    {
        std::cerr << "MenuController::initCurrentMenu - missing MainMenu! Control on menus disabled.\n";
    }
}

void MenuController::showCurrentMenu()
{
    auto currentMenu = currentMenuStack.top();
    currentMenu->second.show();
}

void MenuController::handle(const WidgetCommand& command)
{
    if (auto menu = menus.find(command); menu != std::end(menus))
    {
        currentMenuStack.push(menu);
    }
    else if (command == "Back")
    {
        currentMenuStack.pop();
    }
    else
    {
        auto currentMenu = currentMenuStack.top();
        const WidgetCommand fullWidgetCommand { currentMenu->first + "->" + command };
        if (command == "Abort" or command == "Continue")
        {
            currentMenuStack.pop();
        }
        hideAllMenus();
        menuConnection(convertToMenuCommand(fullWidgetCommand));
        return;
    }

    hideAllMenus();
    showCurrentMenu();
}

MenuCommand MenuController::convertToMenuCommand(const WidgetCommand& widgetCommand)
{
    if (widgetCommand == "SinglePlayer->Play")
    {
        return MenuCommand::StartSinglePlayer;
    }
    if (widgetCommand == "Pause->Abort")
    {
        return MenuCommand::Abort;
    }
    if (widgetCommand == "Pause->Continue")
    {
        return MenuCommand::Continue;
    }
    return MenuCommand::NoCommand;
}

void MenuController::connect(const MenuConnection& connection)
{
    menuConnection = connection;
}

void MenuController::showMenu()
{
    showCurrentMenu();
}
