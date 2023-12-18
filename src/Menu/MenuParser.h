#ifndef MENU_PARSER_H
#define MENU_PARSER_H

#include "Menus.h"
#include <IFileLoader.h>
#include <TextFile.h>
#include <WidgetGeometry.h>
#include <WidgetsFactory.h>
#include <iterator>
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

    void parseStyles(const TextFile& stylesFile);
    static auto parseWidgetStyleContent(
        TextFileContent::const_iterator styleContentBegin,
        TextFileContent::const_iterator styleContentEnd
    ) -> WidgetStyle;
    static auto removeSpaces(const std::string& input) -> std::string;
    auto parseMainMenu(const TextFile& menuFile) -> Menu;
    auto parseWidget(
        const WidgetType& type,
        const TextFileContent& input
    ) -> std::unique_ptr<Widget>;
    static auto parseWidgetGeometry(const std::string& input) -> WidgetGeometry;
    static auto getPositionAfterLabel(
        const std::string& input,
        const std::string& label
    ) -> decltype(std::begin(input));
    static auto parseWidgetText(const std::string& input) -> WidgetText;
    static auto parseTextAfterLabel(
        const std::string& input,
        const std::string& label
    ) -> std::string;
    auto parseWidgetStyle(const std::string& input) -> WidgetStyle;
};

#endif // MENU_PARSER_H
