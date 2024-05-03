#include <FileLoader.h>
#include <MenuController.h>
#include <MenuParser.h>
#include <QApplication>
#include <QMainWindow>
#include <QSize>
#include <QtWidgetsFactory.h>
#include <TextFile.h>
#include <filesystem>
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    QApplication mainApplication(argc, argv);

    auto mainWindow { std::make_shared<QMainWindow>() };
    const int screenWidth { 800 };
    const int screenHeight { 800 };
    mainWindow->setFixedSize(QSize(screenWidth, screenHeight));

    auto widgetFactory { std::make_unique<QtWidgetsFactory>(mainWindow) };
    auto parser { std::make_unique<MenuParser>(std::move(widgetFactory)) };
    Directory dir { std::filesystem::current_path().string() + std::string("/Menus/") };
    auto fileLoader { std::make_unique<FileLoader<TextFile>>(dir) };
    MenuController menuController { std::move(parser), std::move(fileLoader) };

    mainWindow->show();

    return QApplication::exec();
}
