#include "QtGameDisplay.hpp"

QtGameDisplay::QtGameDisplay(const std::shared_ptr<QWidget>& mainWindow)
    : displayImpl(std::make_unique<QGraphicsView>(mainWindow.get()))
{
}

void QtGameDisplay::show()
{
    displayImpl->showFullScreen();
}

void QtGameDisplay::hide()
{
    displayImpl->hide();
}
