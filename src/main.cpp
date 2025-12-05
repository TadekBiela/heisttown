#include "Client/LocalClient.hpp"
#include "FilesStorage/FileLoader.hpp"
#include "FilesStorage/TextFile.hpp"
#include "MainApplication/MainApplication.hpp"
#include "Menu/MenuController.hpp"
#include "Menu/MenuParser.hpp"
#include "Sfml/DisplaySfml.hpp"
#include "Sfml/SfmlWidgets/WidgetsFactorySfml.hpp"
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
    auto textureStorage { std::make_shared<FilesStorage<TextureFile>>(std::make_unique<FileLoader<TextureFile>>(std::filesystem::current_path().string() + "/Sfml/Textures/")) };
    auto menuDisplaySfml { std::make_shared<DisplaySfml>(1000, 800, textureStorage) };
    const auto currentPath { std::filesystem::current_path() };
    auto widgetsFactory { std::make_unique<WidgetsFactorySfml>(getLoadedFont(currentPath), menuDisplaySfml) };
    auto menuParser { std::make_unique<MenuParser>(std::move(widgetsFactory)) };

    const auto menuFilePath { currentPath.string() + "/Menus/" };
    auto menuFileLoader { std::make_unique<FileLoader<TextFile>>(menuFilePath) };
    auto menuController { std::make_unique<MenuController>(std::move(menuParser), std::move(menuFileLoader)) };

    // std::unique_ptr<PlayerInputSfml> input;

    auto mainApplication { std::make_unique<MainApplication>(std::move(menuController), menuDisplaySfml, nullptr, []() {}) };
    mainApplication->run();
    menuDisplaySfml->display();
    return 0;
}
