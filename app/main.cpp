#include <QApplication>
#include <QMainWindow>
#include <QSize>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setFixedSize(QSize(800, 600));
    mainWindow.show();

    return a.exec();
}

