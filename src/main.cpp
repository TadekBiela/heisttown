#include <QApplication>
#include <QMainWindow>
#include <QSize>

auto main(int argc, char* argv[]) -> int
{
    QApplication mainApplication(argc, argv);

    QMainWindow mainWindow;
    const int screenWidth { 800 };
    const int screenHeight { 800 };
    mainWindow.setFixedSize(QSize(screenWidth, screenHeight));
    mainWindow.show();

    return QApplication::exec();
}
