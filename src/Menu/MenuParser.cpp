#include "MenuParser.h"
#include "Menu.h"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iterator>

MenuParser::MenuParser(std::unique_ptr<WidgetsFactory> factory)
    : widgetsFactory(std::move(factory))
{
}

auto MenuParser::parse(std::unique_ptr<IFileLoader<TextFile>> input) -> Menus
{
    auto filesToParse = input->getLoadedData();
    Menus parsedMenus;

    if (filesToParse.count("Styles") != 0)
    {
        parseStyles(filesToParse.at("Styles"));
    }

    if (filesToParse.count("MainMenu") != 0)
    {
        parsedMenus.push_back(parseMainMenu(filesToParse.at("MainMenu")));
    }
    return parsedMenus;
}

void MenuParser::parseStyles(const TextFile& stylesFile)
{
    for (auto line = std::begin(stylesFile.getContent()); line != std::end(stylesFile.getContent()); line++)
    {
        if (line->find("@") != std::string::npos)
        {
            WidgetStyleName styleName(std::next(std::begin(*line)), std::prev(std::end(*line)));
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

auto MenuParser::parseMainMenu(const TextFile& menuFile) -> Menu
{
    Menu mainMenu;

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
        TextFileContent widgetPartOfContent { std::next(line), std::next(line, amountOfWidgetParams) };
        mainMenu.addWidget(parseWidget(type, widgetPartOfContent));
    }

    return mainMenu;
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
    const int amoutOfGeometryParams { 4 };
    std::array<int, amoutOfGeometryParams> geometryValues {};
    auto valueStrBegin = getPositionAfterLabel(input, "geometry: ");

    for (auto& geometryValue : geometryValues)
    {
        const char valueSeparator { ',' };
        auto valueStrEnd = std::find(valueStrBegin, std::end(input), valueSeparator);
        std::string valueStr(valueStrBegin, valueStrEnd);
        geometryValue = std::atoi(valueStr.c_str());
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
