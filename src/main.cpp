#include <FileLoader.hpp>
#include <LocalClient.hpp>
#include <MainApplication.hpp>
#include <MenuController.hpp>
#include <MenuParser.hpp>
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QtGameDisplay.hpp>
#include <QtWidgetsFactory.hpp>
#include <TextFile.hpp>
#include <filesystem>
#include <iostream>
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    QApplication application(argc, argv);

    auto mainWindow { std::make_shared<QMainWindow>() };
    mainWindow->setWindowState(Qt::WindowFullScreen);

    auto widgetFactory { std::make_unique<QtWidgetsFactory>(mainWindow) };
    auto parser { std::make_unique<MenuParser>(std::move(widgetFactory)) };
    Directory dir { std::filesystem::current_path().string() + std::string("/Menus/") };
    auto fileLoader { std::make_unique<FileLoader<TextFile>>(dir) };
    auto menuController { std::make_unique<MenuController>(std::move(parser), std::move(fileLoader)) };

    auto gameDisplay { std::make_unique<QtGameDisplay>(mainWindow) };
    auto client { std::make_unique<LocalClient>(std::move(gameDisplay)) };

    MainApplication mainApplication { std::move(menuController), std::move(client) };

    mainWindow->show();

    return QApplication::exec();
}
