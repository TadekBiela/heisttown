#ifndef MENU_PARSER_H
#define MENU_PARSER_H

#include "Menus.h"
#include <IFileLoader.h>
#include <TextFile.h>
#include <WidgetGeometry.h>
#include <WidgetsFactory.h>
#include <memory>
#include <string>

using WidgetStyleName = std::string;

class MenuParser
{
public:
    MenuParser(std::unique_ptr<WidgetsFactory> factory);
    virtual ~MenuParser() = default;

    auto parse(std::unique_ptr<IFileLoader<TextFile>> input) -> Menus;

private:
    const std::shared_ptr<WidgetsFactory> widgetsFactory;
    std::map<WidgetStyleName, WidgetStyle> parsedStyles {};

    auto parseButtonWidget(const TextFileContent& input) -> std::unique_ptr<Widget>;
    static auto parseWidgetGeometry(const std::string& input) -> WidgetGeometry;
    static auto parseWidgetText(const std::string& input) -> WidgetText;
    auto parseWidgetStyle(const std::string& input) -> WidgetStyle;
};

#endif // MENU_PARSER_H
