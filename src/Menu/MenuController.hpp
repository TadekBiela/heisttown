#pragma once

#include "IMenuController.hpp"
#include "IMenuParser.hpp"
#include "Menus.hpp"
#include <IFileLoader.hpp>
#include <TextFile.hpp>
#include <WidgetControl.hpp>
#include <memory>
#include <stack>

class MenuController : public IMenuController
{
public:
    MenuController(
        std::unique_ptr<IMenuParser> parser,
        std::unique_ptr<IFileLoader<TextFile>> source
    );

    void handle(const WidgetCommand& command) override;
    void connect(const MenuConnection& connection) override;
    void showMenu() override;

protected:
    Menus menus;
    std::stack<Menus::iterator> currentMenuStack;

private:
    ControlConnection controlConnection;
    MenuConnection menuConnection { [](const MenuCommand&){} };

    void hideAllMenus();
    void connectMenus();
    void initCurrentMenu();
    void showCurrentMenu();
    static MenuCommand convertToMenuCommand(const WidgetCommand& widgetCommand);
};
