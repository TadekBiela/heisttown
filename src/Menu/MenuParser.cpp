#include "MenuParser.h"
#include "Menu.h"
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <string>

MenuParser::MenuParser(std::unique_ptr<WidgetsFactory> factory)
    : widgetsFactory(std::move(factory))
{
}

auto MenuParser::parse(std::unique_ptr<IFileLoader<TextFile>> input) const -> Menus
{
    auto filesToParse = input->getLoadedData();
    Menus parsedMenus;
    if (filesToParse.count("MainMenu") != 0)
    {
        TextFile menuFile { filesToParse.at("MainMenu") };
        Menu mainMenu;
        for (auto line = std::begin(menuFile.getContent()); line != std::end(menuFile.getContent()); line++)
        {
            if (line->find("Button:") != std::string::npos)
            {
                line++;
                auto xStrBegin = std::find(std::begin(*line), std::end(*line), ':') + 1;
                auto xStrEnd = std::find(xStrBegin, std::end(*line), ',');
                std::string xStr(xStrBegin, xStrEnd);

                auto yStrBegin = xStrEnd + 1;
                auto yStrEnd = std::find(yStrBegin, std::end(*line), ',');
                std::string yStr(yStrBegin, yStrEnd);

                auto widthStrBegin = yStrEnd + 1;
                auto widthStrEnd = std::find(widthStrBegin, std::end(*line), ',');
                std::string widthStr(widthStrBegin, widthStrEnd);

                auto heightStrBegin = widthStrEnd + 1;
                std::string heightStr(heightStrBegin, std::end(*line));

                line++;
                auto textBegin = std::find(std::begin(*line), std::end(*line), ':') + 2;
                std::string textStr(textBegin, std::end(*line));

                mainMenu.addWidget(widgetsFactory->create(WidgetType::BUTTON, { std::atoi(xStr.c_str()), std::atoi(yStr.c_str()), std::atoi(widthStr.c_str()), std::atoi(heightStr.c_str()) }, textStr, ""));
            }
        }
        parsedMenus.push_back(std::move(mainMenu));
    }
    return parsedMenus;
}
