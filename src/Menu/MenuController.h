#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "ControlWidget.h"
#include "IMenuParser.h"
#include "Menus.h"
#include <IFileLoader.h>
#include <TextFile.h>
#include <memory>

using MainCommand = std::string;
using MainControlConnection = std::function<void(const MainCommand&)>;

class MenuController
{
public:
    MenuController(
        std::unique_ptr<IMenuParser> parser,
        std::unique_ptr<IFileLoader<TextFile>> source,
        const MainControlConnection& mainControlConnection
    );

    void control(const WidgetCommand& command);

protected:
    const MainControlConnection& mainControlConnection;
    Menus menus;
    Menus::iterator currentMenu;
    Menus::iterator previousMenu;

private:
    ControlConnection controlConnection;

    void connectMenus();
    void initCurrentMenu();
    void hideAllMenus();
};

#endif // MENU_CONTROLLER_H
