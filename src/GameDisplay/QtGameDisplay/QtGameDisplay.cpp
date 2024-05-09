#include "QtGameDisplay.hpp"
#include <QScreen>

QtGameDisplay::QtGameDisplay(const std::shared_ptr<QWidget>& mainWindow)
    : displayImpl(std::make_unique<QGraphicsView>(mainWindow.get()))
{
    displayImpl->hide();
    displayImpl->setGeometry(mainWindow->screen()->geometry());
}

void QtGameDisplay::show()
{
    displayImpl->show();
}

void QtGameDisplay::hide()
{
    displayImpl->hide();
}
