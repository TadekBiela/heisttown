#pragma once

#include "IMenuParser.hpp"
#include "Menus.hpp"
#include <IFileLoader.hpp>
#include <TextFile.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetsFactory.hpp>
#include <iterator>
#include <map>
#include <memory>
#include <string>

using WidgetStyleName = std::string;

class MenuParser : public IMenuParser
{
public:
    explicit MenuParser(std::unique_ptr<WidgetsFactory> factory);

    Menus&& parse(std::unique_ptr<IFileLoader<TextFile>> input) override;

private:
    const std::unique_ptr<WidgetsFactory> widgetsFactory;
    std::map<WidgetStyleName, WidgetStyle> parsedStyles;
    Menus parsedMenus;
    Menu menu;

    void parseStyles(const TextFile& stylesFile);
    static WidgetStyle parseWidgetStyleContent(
        TextFileContent::const_iterator styleContentBegin,
        TextFileContent::const_iterator styleContentEnd
    );
    static std::string removeSpaces(const std::string& input);
    Menu&& parseMenu(const TextFile& menuFile);
    std::unique_ptr<Widget> parseWidget(
        const WidgetType& type,
        const TextFileContent& input
    );
    static WidgetGeometry parseWidgetGeometry(const std::string& input);
    static auto getPositionAfterLabel(
        const std::string& input,
        const std::string& label
    ) -> decltype(std::begin(input));
    static WidgetText parseWidgetText(const std::string& input);
    static std::string parseTextAfterLabel(
        const std::string& input,
        const std::string& label
    );
    WidgetStyle parseWidgetStyle(const std::string& input);
};
