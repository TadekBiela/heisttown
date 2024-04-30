#include "MenuController.h"

MenuController::MenuController(
    std::unique_ptr<IMenuParser> parser,
    std::unique_ptr<IFileLoader<TextFile>> source
)
{
    menus = parser->parse(std::move(source));
}

void MenuController::hideAllMenus()
{
    for (auto& menu : menus)
    {
        menu.hide();
    }
}
