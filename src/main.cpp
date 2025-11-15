#include "Client/LocalClient.hpp"
#include "FilesStorage/FileLoader.hpp"
#include "FilesStorage/TextFile.hpp"
#include "MainApplication/MainApplication.hpp"
#include "Menu/MenuController.hpp"
#include "Menu/MenuParser.hpp"
#include "Sfml/DisplaySfml.hpp"
#include "Sfml/WidgetsFactorySfml.hpp"
#include <SFML/Graphics/Font.hpp>
#include <filesystem>
#include <memory>
#include <thread>

std::shared_ptr<sf::Font> getLoadedFont(const std::filesystem::path& currentPath)
{
    const auto fontPath { currentPath.string() + "/Sfml/Font/PixelCode.ttf" };
    auto font { std::make_shared<sf::Font>() };
    font->loadFromFile(fontPath);

    return font;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    auto menuDisplaySfml { std::make_shared<DisplaySfml>(1000, 800) };
    const auto currentPath { std::filesystem::current_path() };
    auto widgetsFactory { std::make_unique<WidgetsFactorySfml>(getLoadedFont(currentPath), menuDisplaySfml) };
    auto menuParser { std::make_unique<MenuParser>(std::move(widgetsFactory)) };

    const auto menuFilePath { currentPath.string() + "/Menus/" };
    auto menuFileLoader { std::make_unique<FileLoader<TextFile>>(menuFilePath) };
    auto menuController { std::make_unique<MenuController>(std::move(menuParser), std::move(menuFileLoader)) };

    // std::unique_ptr<PlayerInputSfml> input;
    auto client { std::make_shared<LocalClient>(menuDisplaySfml, nullptr) };

    auto mainApplication { std::make_unique<MainApplication>(std::move(menuController), std::move(client), []() {}) };
    mainApplication->run();
    menuDisplaySfml->display();
    return 0;
}
