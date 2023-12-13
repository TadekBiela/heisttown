#ifndef MENU_PARSER_H
#define MENU_PARSER_H

#include "Menus.h"
#include <IFileLoader.h>
#include <TextFile.h>
#include <WidgetsFactory.h>
#include <memory>

class MenuParser
{
public:
    MenuParser(std::unique_ptr<WidgetsFactory> factory);
    virtual ~MenuParser() = default;

    auto parse(std::unique_ptr<IFileLoader<TextFile>> input) const -> Menus;

private:
    const std::shared_ptr<WidgetsFactory> widgetsFactory;
};

#endif // MENU_PARSER_H
