#ifndef MENU_CONTROLLER_HPP
#define MENU_CONTROLLER_HPP

#include "ControlWidget.hpp"
#include "IMenuController.hpp"
#include "IMenuParser.hpp"
#include "Menus.hpp"
#include <IFileLoader.hpp>
#include <MainControlConnector.hpp>
#include <TextFile.hpp>
#include <memory>
#include <stack>

class MenuController : public IMenuController
{
public:
    MenuController(
        std::unique_ptr<IMenuParser> parser,
        std::unique_ptr<IFileLoader<TextFile>> source
    );

    void control(const WidgetCommand& command) override;
    void showMenu() override;
    void setMainControl(const MainControlConnection& controlConnection) override;

protected:
    MainControlConnection mainControlConnection { [](const WidgetCommand&){} };
    Menus menus;
    std::stack<Menus::iterator> currentMenuStack;

private:
    ControlConnection controlConnection;

    void hideAllMenus();
    void connectMenus();
    void initCurrentMenu();
    void showCurrentMenu();
};

#endif // MENU_CONTROLLER_HPP
