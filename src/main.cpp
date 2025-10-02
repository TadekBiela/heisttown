#include "Client/LocalClient.hpp"
#include "FilesStorage/FileLoader.hpp"
#include "FilesStorage/TextFile.hpp"
#include "MainApplication/MainApplication.hpp"
#include "Menu/MenuController.hpp"
#include "Menu/MenuParser.hpp"
#include "Sfml/EventDispatcher.hpp"
#include "Sfml/Renderer.hpp"
#include "Sfml/WidgetsFactorySfml.hpp"
#include <SFML/Graphics/Font.hpp>
#include <filesystem>
#include <memory>
#include <thread>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    auto menuRenderer { std::make_shared<Renderer>(1000, 800) };
    auto menuEventDispatcher { std::make_shared<EventDispatcher>() };

    const auto currentPath { std::filesystem::current_path() };
    const auto fontPath { currentPath.string() + "/Sfml/Font/PixelCode.ttf" };
    auto font { std::make_shared<sf::Font>() };
    font->loadFromFile(fontPath);
    auto widgetsFactory { std::make_unique<WidgetsFactorySfml>(font, menuRenderer, menuEventDispatcher) };
    auto menuParser { std::make_unique<MenuParser>(std::move(widgetsFactory)) };

    const auto menuFilePath { currentPath.string() + "/Menus/" };
    auto menuFileLoader { std::make_unique<FileLoader<TextFile>>(menuFilePath) };
    auto menuController { std::make_unique<MenuController>(std::move(menuParser), std::move(menuFileLoader)) };

    menuController->showMenu();

    std::thread eventThread { &EventDispatcher::dispatch, *menuEventDispatcher, std::ref(menuRenderer->getWindow()) };
    menuRenderer->render();
    eventThread.join();
    return 0;
}
