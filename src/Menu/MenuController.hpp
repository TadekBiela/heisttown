#ifndef MENU_CONTROLLER_HPP
#define MENU_CONTROLLER_HPP

#include "ControlWidget.hpp"
#include "IMenuParser.hpp"
#include "Menus.hpp"
#include <IFileLoader.hpp>
#include <TextFile.hpp>
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

#endif // MENU_CONTROLLER_HPP
