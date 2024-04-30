#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

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

protected:
    Menus menus;

private:
    void hideAllMenus();
};

#endif // MENU_CONTROLLER_H
