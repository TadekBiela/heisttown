#include "MenuParser.hpp"
#include "Menu.hpp"
#include "Menus.hpp"
#include <IFileLoader.hpp>
#include <TextFile.hpp>
#include <Widget.hpp>
#include <WidgetGeometry.hpp>
#include <WidgetType.hpp>
#include <WidgetsFactory.hpp>
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <string>
#include <utility>

MenuParser::MenuParser(std::unique_ptr<WidgetsFactory> factory)
    : widgetsFactory(std::move(factory))
{
}

auto MenuParser::parse(std::unique_ptr<IFileLoader<TextFile>> input) -> Menus&&
{
    auto filesToParse = input->getLoadedData();

    if (auto styles { filesToParse.find("Styles") }; styles != std::end(filesToParse))
    {
        parseStyles(styles->second);
        filesToParse.erase(styles);
    }
    else
    {
        std::cerr << "MenuParser::parse - missing Styles.txt file. No styles parsed!\n";
    }

    for (const auto& fileToParse : filesToParse)
    {
        parsedMenus[fileToParse.first] = parseMenu(fileToParse.second);
    }
    return std::move(parsedMenus);
}

void MenuParser::parseStyles(const TextFile& stylesFile)
{
    for (auto line = std::begin(stylesFile.getContent()); line != std::end(stylesFile.getContent()); line++)
    {
        if (line->find("@") != std::string::npos)
        {
            const WidgetStyleName styleName(std::next(std::begin(*line)), std::prev(std::end(*line)));
            parsedStyles[styleName] = parseWidgetStyleContent(std::next(line), std::end(stylesFile.getContent()));
        }
    }
}

auto MenuParser::parseWidgetStyleContent(
    TextFileContent::const_iterator styleContentBegin,
    TextFileContent::const_iterator styleContentEnd
) -> WidgetStyle
{
    WidgetStyle styleContent;
    for (auto styleContentIt = styleContentBegin; styleContentIt != styleContentEnd; styleContentIt++)
    {
        if (styleContentIt->find("@") != std::string::npos)
        {
            break;
        }
        styleContent += removeSpaces(*styleContentIt);
    }
    return styleContent;
}

auto MenuParser::removeSpaces(const std::string& input) -> std::string
{
    std::string line { input };
    line.erase(std::remove(std::begin(line), std::end(line), ' '), std::end(line));
    return line;
}

auto MenuParser::parseMenu(const TextFile& menuFile) -> Menu&&
{
    menu = {};
    std::cout << "parsing: " << menuFile.getPath() << "\n";
    for (auto line = std::begin(menuFile.getContent()); line != std::end(menuFile.getContent()); line++)
    {
        WidgetType type {};
        if (line->find("Button:") != std::string::npos)
        {
            type = WidgetType::BUTTON;
        }
        else if (line->find("Label:") != std::string::npos)
        {
            type = WidgetType::LABEL;
        }
        else
        {
            continue;
        }

        const int amountOfWidgetParams { 4 };
        const TextFileContent widgetPartOfContent { std::next(line), std::next(line, amountOfWidgetParams) };
        menu.addWidget(parseWidget(type, widgetPartOfContent));
    }

    return std::move(menu);
}

auto MenuParser::parseWidget(
    const WidgetType& type,
    const TextFileContent& input
) -> std::unique_ptr<Widget>
{
    return widgetsFactory->create(
        type,
        parseWidgetGeometry(input.at(0)),
        parseWidgetText(input.at(1)),
        parseWidgetStyle(parseTextAfterLabel(input.at(2), "style: "))
    );
}

auto MenuParser::parseWidgetGeometry(const std::string& input) -> WidgetGeometry
{
    constexpr int amoutOfGeometryParams { 4 };
    std::array<float, amoutOfGeometryParams> geometryValues {};
    auto valueStrBegin = getPositionAfterLabel(input, "geometry: ");

    for (auto& geometryValue : geometryValues)
    {
        const char valueSeparator { ',' };
        auto valueStrEnd = std::find(valueStrBegin, std::end(input), valueSeparator);
        const std::string valueStr(valueStrBegin, valueStrEnd);
        geometryValue = std::strtof(valueStr.c_str(), nullptr);
        valueStrBegin = std::next(valueStrEnd);
    }

    return WidgetGeometry { geometryValues[0], geometryValues[1], geometryValues[2], geometryValues[3] };
}

auto MenuParser::getPositionAfterLabel(
    const std::string& input,
    const std::string& label
) -> decltype(std::begin(input))
{
    return std::next(std::begin(input), static_cast<int>(input.find(label) + label.size()));
}

auto MenuParser::parseWidgetText(const std::string& input) -> WidgetText
{
    return parseTextAfterLabel(input, "text: ");
}

auto MenuParser::parseTextAfterLabel(
    const std::string& input,
    const std::string& label
) -> std::string
{
    auto textBegin = getPositionAfterLabel(input, label);
    std::string textStr(textBegin, std::end(input));
    return textStr;
}

auto MenuParser::parseWidgetStyle(const std::string& input) -> WidgetStyle
{
    if (input.find("none") != std::string::npos || parsedStyles.count(input) == 0)
    {
        return WidgetStyle { "" };
    }

    return parsedStyles.at(input);
}
