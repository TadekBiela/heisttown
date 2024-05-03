#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "DynamicWidget.h"
#include "IMenuParser.h"
#include "Menus.h"
#include <IFileLoader.h>
#include <TextFile.h>
#include <memory>

class MenuController
{
public:
    MenuController(
        std::unique_ptr<IMenuParser> parser,
        std::unique_ptr<IFileLoader<TextFile>> source
    );

    void control(const WidgetMessage& message);

protected:
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
