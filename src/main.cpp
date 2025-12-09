#include "Client/LocalClient.hpp"
#include "FilesStorage/FileLoader.hpp"
#include "FilesStorage/TextFile.hpp"
#include "MainApplication/MainApplication.hpp"
#include "Menu/MenuController.hpp"
#include "Menu/MenuParser.hpp"
#include "Sfml/DisplaySfml.hpp"
#include "Sfml/SfmlRendering/SfmlTextureFile.hpp"
#include "Sfml/SfmlWidgets/WidgetsFactorySfml.hpp"
#include <SFML/Graphics/Font.hpp>
#include <filesystem>
#include <memory>
#include <thread>

std::shared_ptr<sf::Font> getLoadedFont(const std::string& assetsPath)
{
    const auto fontPath { assetsPath + "Font/PixelCode.ttf" };
    auto font { std::make_shared<sf::Font>() };
    font->loadFromFile(fontPath);

    return font;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    const auto assetsPath { std::filesystem::current_path().string() + "/Assets/" };
    auto textureStorage { std::make_unique<FilesStorage<SfmlTextureFile>>(std::make_unique<FileLoader<SfmlTextureFile>>(assetsPath + "Textures/")) };
    auto menuDisplaySfml { std::make_shared<DisplaySfml>(1000, 800, std::move(textureStorage)) };

    auto widgetsFactory { std::make_unique<WidgetsFactorySfml>(getLoadedFont(assetsPath), menuDisplaySfml) };
    auto menuParser { std::make_unique<MenuParser>(std::move(widgetsFactory)) };

    const auto menuFilePath { assetsPath + "Menus/" };
    auto menuFileLoader { std::make_unique<FileLoader<TextFile>>(menuFilePath) };
    auto menuController { std::make_unique<MenuController>(std::move(menuParser), std::move(menuFileLoader)) };

    // std::unique_ptr<InputSfml> input;

    auto mainApplication { std::make_unique<MainApplication>(std::move(menuController), menuDisplaySfml, nullptr, []() {}) };
    mainApplication->run();
    menuDisplaySfml->display();
    return 0;
}
