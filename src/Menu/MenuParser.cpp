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
        TextFile stylesFile { filesToParse.at("Styles") };
        for (auto line = std::begin(stylesFile.getContent()); line != std::end(stylesFile.getContent()); line++)
        {
            if (line->find("@") != std::string::npos)
            {
                WidgetStyleName styleName(std::next(std::begin(*line)), std::prev(std::end(*line)));
                WidgetStyle styleContent;
                for (auto styleContentIt = std::next(line); styleContentIt != std::end(stylesFile.getContent()); styleContentIt++)
                {
                    if (styleContentIt->find("@") != std::string::npos)
                    {
                        break;
                    }
                    std::string line{*styleContentIt};
                    line.erase(std::remove(std::begin(line), std::end(line), ' '), std::end(line));
                    styleContent += line;
                }
                parsedStyles[styleName] = styleContent;
            }
        }
    }

    if (filesToParse.count("MainMenu") != 0)
    {
        TextFile menuFile { filesToParse.at("MainMenu") };
        Menu mainMenu;
        for (auto line = std::begin(menuFile.getContent()); line != std::end(menuFile.getContent()); line++)
        {
            if (line->find("Button:") != std::string::npos)
            {
                TextFileContent buttonPartOfContent { std::next(line), std::next(line, 4) };
                mainMenu.addWidget(parseButtonWidget(buttonPartOfContent));
            }
        }
        parsedMenus.push_back(std::move(mainMenu));
    }
    return parsedMenus;
}

auto MenuParser::parseButtonWidget(const TextFileContent& input) -> std::unique_ptr<Widget>
{
    auto widgetGeometry { parseWidgetGeometry(input.at(0)) };
    auto widgetText { parseWidgetText(input.at(1)) };
    auto widgetStyle { parseWidgetStyle(parseWidgetText(input.at(2))) };
    return widgetsFactory->create(WidgetType::BUTTON, widgetGeometry, widgetText, widgetStyle);
}

auto MenuParser::parseWidgetGeometry(const std::string& input) -> WidgetGeometry
{
    const int amoutOfGeometryParams { 4 };
    std::array<int, amoutOfGeometryParams> geometryValues;
    auto valueStrBegin = std::next(std::find(std::begin(input), std::end(input), ':'));

    for(auto& geometryValuesIdx : geometryValues)
    {
        auto valueStrEnd = std::find(valueStrBegin, std::end(input), ',');
        std::string valueStr(valueStrBegin, valueStrEnd);
        geometryValuesIdx = std::atoi(valueStr.c_str());
        valueStrBegin = std::next(valueStrEnd);
    }

    return WidgetGeometry { geometryValues[0], geometryValues[1], geometryValues[2], geometryValues[3] };
}

auto MenuParser::parseWidgetText(const std::string& input) -> WidgetText
{
    auto textBegin = std::next(std::find(std::begin(input), std::end(input), ':'), 2);
    std::string textStr(textBegin, std::end(input));
    return textStr;
}

auto MenuParser::parseWidgetStyle(const std::string& input) -> WidgetStyle
{
    if(input.find("none") != std::string::npos || parsedStyles.count(input) == 0)
    {
        return WidgetStyle{""};
    }

    return parsedStyles.at(input);
}
